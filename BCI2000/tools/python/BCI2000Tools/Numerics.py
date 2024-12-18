# -*- coding: utf-8 -*-

# ///////////////////////////////////////////////////////////////////////////
# $Id: Numerics.py 8274 2024-07-24 22:13:30Z jhill $
# Author: jeremy.hill@neurotechcenter.org
# Description: numerical helper functions for time-series analysis
#
# $BEGIN_BCI2000_LICENSE$
#
# This file is part of BCI2000, a platform for real-time bio-signal research.
# [ Copyright (C) 2000-2022: BCI2000 team and many external contributors ]
#
# BCI2000 is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# BCI2000 is distributed in the hope that it will be useful, but
#                         WITHOUT ANY WARRANTY
# - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
#
# $END_BCI2000_LICENSE$
# ///////////////////////////////////////////////////////////////////////////

__all__ = [
	'pdiff',
	'unwrapdiff',
	
	'mad',

	'edges',
	'events',
	'refrac',
	'epochs',
	'match_events',
]

import numpy

def pdiff( x, order=1, axis=-1, pBefore=0.5, padVal=0 ):
	"""
	Padded diff. Take a numerical diff of order `order` along axis
	`axis`, but return a result that is the same size and shape as
	the input `x`. Do this by padding the result with zeros (or
	copies of the value `padVal`, if non-zero) at the beginning and
	end.

	The proportion of padding at the beginning, as opposed to the
	end, is given by `pBefore`, which defaults to 0.5. For odd
	values of `order`, the number of values to be padded at the
	beginning is rounded, with 0.5 always being rounded up---so,
	by default, with `order=1`, the result will be padded with a
	single zero at the beginning and nothing at the end.

	This results in the following default behavior, which is quite
	natural for plotting:

	>>> pdiff([1,2,4])
	array([0, 1, 2])

	>>> pdiff([1,2,4], order=2)
	array([0, 1, 0])

	>>> pdiff([1,2,4], pBefore=0)
	array([1, 2, 0])

	"""
	# uses: numpy
	order = int( order )
	nBefore = int( 0.5 + pBefore * order )
	nAfter = order - nBefore
	x = numpy.asarray( x )
	if numpy.issubdtype( x.dtype, numpy.unsignedinteger ): x = x.astype( 'int64' )
	if x.ndim == 0: x = x.flatten()
	sub = [ slice( None ) for i in x.shape ]
	sub[ axis ] = slice( nBefore, x.shape[ axis ] - nAfter )
	dx = numpy.zeros_like( x )
	if( padVal ): dx.fill( padVal )
	dx[ tuple( sub ) ] = numpy.diff( x, n=order, axis=axis )
	return dx

def unwrapdiff( x, base=2*numpy.pi, axis=None, startval=None, dtype=None, padded=True ):
	"""
	Assume `x` is a wrapped version of an underlying value `y` we're
	interested in. For example, it's a 16-bit value that wraps around
	at 65536, or it's an angle which wraps back to 0 at 2*pi.
	
	`base` is the value (65536 or 2*pi in the above examples) such
	that `x = y % base`.  The default value of `base` is 2*pi.
	
	Let `dy` be the numeric diff of `y` in dimension `axis`, computed
	from `x` by unwrapping in order to avoid jumps larger than
	`base/2`.  Thus with `base=65536`, a jump from 65535 to 1 is
	considered as a step of +2. With `base=360`, a jump from 10 to
	350 is considered as a step of -20.
	
	`y` is then reconstructed based on `dy` and `startval` (which
	defaults to the actual initial value(s) of `x`).
	
	The Return value is `(dy, y)`. With `padded=True`, `dy` will be
	zero-padded at the beginning such that it is the same shape as
	`y`. With `padded=False`, it will be shorter by 1 along the
	relevant `axis`, like a normal `numpy.diff`.
	"""
	# uses: numpy
	x = numpy.asarray( x, dtype=dtype )
	if numpy.issubdtype( x.dtype, numpy.unsignedinteger ): x = x.astype( 'int64' )
	if axis is None:
		axis, = numpy.where( numpy.array( x.shape ) != 1 )
		if len( axis ): axis = axis[ 0 ]
		else: axis = 0
	x = x % base
	sub = [ slice( None ) for i in x.shape ]
	dFull = d = numpy.diff( x, axis=axis )
	if padded:
		sub[ axis ] = slice( 1, None )
		dFull = numpy.zeros_like( x )
		dFull[ tuple( sub ) ] = d
		d = dFull[ tuple( sub ) ] # d is now a slice into dFull
	nj = d < -base / 2.0
	d[ nj ] += base
	pj = d > base / 2.0
	d[ pj ] -= base
	d[ numpy.isnan( d ) ] = 0
	sub[ axis ] = [ 0 ]
	sv = x[ tuple( sub ) ]
	if startval is not None: sv = sv * 0 + startval
	x = numpy.cumsum( numpy.concatenate( ( sv, d ), axis=axis ), axis=axis )
	return dFull, x

def mad( a, b=None, axis=None ):
	"""
	Maximum absolute difference between two arrays (or maximum absolute
	value of one array) along a certain axis (if given) or among all
	elements (if not).
	"""
	# uses: numpy
	if b is not None:
		a = numpy.asarray(a).view()
		b = numpy.asarray(b).view()
		a.shape = tuple( a.shape ) + ( 1, ) * ( max( b.ndim, axis + 1 if axis else 1 ) - a.ndim )
		b.shape = tuple( b.shape ) + ( 1, ) * ( max( a.ndim, axis + 1 if axis else 1 ) - b.ndim )
		if a.size != 1 and b.size != 1 and a.shape != b.shape: raise ValueError('unmatched shapes')
		a = a - b
	a = numpy.abs( a )
	if axis is not None: a.shape = tuple( a.shape ) + ( 1, ) * ( axis + 1 - a.ndim )
	return numpy.max( a, axis=axis )

def edges( x, axis=-1, direction=+1, exceed=0.0, return_logical=False ):
	"""
	Returns a set of indices marking rising edges of `x` (or falling
	edges, if `direction` is -1) working along the dimension `axis`.
	
	Often you will want to threshold your signal *before* passing it
	in, e.g.  `edges(signal > threshold)`, in which case the function
	offers no more or less functionality than `events()`. However
	it is also possible to customize the `exceed` parameter, thereby
	defining an edge as any jump in the specified `direction` whose
	size is greater than `exceed`.
	
	By default, one index is returned per slice across the given
	`axis` in which *any* element meets the criterion (so, if you
	have a multichannel signal, an edge is recorded if it happens
	in any of the channels). Alternatively, with `return_logical=True`,
	instead of an array of indices, a logical array the same size
	as `x` is returned, wherein the edges are marked True---this
	preserves the independent behaviour of different channels.
	
	You might want to pass the indices to `refrac()` and/or `epochs()`.
	
	See also `events()` which is similar, but more suitable for
	finding changes in time series whose values are digital or
	categorical.
	"""
	# uses: numpy,  pdiff()
	x = numpy.asarray( x, dtype=numpy.float64 )
	dx = pdiff( x, axis=axis )
	dx = direction * dx if direction else numpy.abs( dx )
	edges = ( dx > exceed )
	return edges if return_logical else sorted( set( edges.nonzero()[ axis ] ) )

def events( x, axis=-1, include=None, exclude=0, return_logical=False ):
	"""
	Returns a set of indices marking places where `x` changes its
	value, working along the dimension `axis`.
	
	If `include` is given (i.e. not `None`), only consider changes
	to one of the specified values. If `exclude` is given, ignore
	changes to any of the specified values. The default settings,
	`include=None` and `exclude=0`, ensure that all changes are
	considered except changes to 0.
	
	With `return_logical=True`, instead of an array of indices, a
	logical array the same size as `x` is returned, wherein the
	events are marked `True`.
	
	You might want to pass the indices to `refrac()` and/or `epochs()`.
	
	See also `edges()` which is similar, but more suitable for finding
	rising or falling edges in continuous-valued signals.
	"""
	# uses: numpy,  pdiff()
	events = pdiff( x, axis=axis ) != 0
	if exclude is not None:
		for value in numpy.asarray( exclude ).flat:
			events &= ( x != value )
	if include is not None:
		mask = numpy.zeros_like( events )
		for value in numpy.asarray( include ).flat:
			mask |= ( x == value )
		events &= mask
	return events if return_logical else sorted( set( events.nonzero()[ axis ] ) )

def refrac( indices, interval, fs=1.0 ):
	"""
	Given an ascending sequence of `indices` (expressed in samples)
	remove those that occur too close together. In other words,
	remove any index that is less than `interval` away from its
	predecessor, where `interval` is expressed in samples by default,
	but may be expressed in other time units if the number of samples
	per time unit is supplied as `fs`.
	
	You may often wish to call this function on the results of
	`edges()` before proceeding to `epochs()`, although you can also
	tell `epochs()` to call `refrac()` automatically for you.	
	"""
	# uses: numpy
	if isinstance( indices, numpy.ndarray ):
		indices = indices.flatten()
		if indices.dtype == bool:
			if indices.size != max( indices.shape ): raise ValueError( "if a logical array is supplied, it should only have one non-singleton dimension" )
			indices = indices.nonzero()[ 0 ]
	interval_samples = int( 0.5 + float( fs ) * interval )
	out, previous = [], None
	for ind in indices:
		if previous is None or ind - previous >= interval_samples:
			out.append( int( ind ) )
			previous = ind
	if isinstance( indices, numpy.ndarray ): out = numpy.array( out )
	return out

def epochs( x, start_indices, length, offset=0, refractory=0, fs=1.0, axis=-1, return_partial=False, return_array=False ):
	"""
	Returns three outputs: `epochlist`, `timebase`, `indices_used`.
	 
	`epochlist` is a list of arrays (or a numpy array if
	`return_array` is set to `True`).  Each array in the list is a
	slice of `x` along the specified `axis`, starting at the
	corresponding index in the sequence of `start_indices`. You
	probably found the start indices using the `edges()` or
	`events()` function.
	
	Slices continue along axis `axis` for a number of samples specified
	by `length`.  By default `length` is expressed in samples, but it
	is also possible to express it in other time units if you pass the
	number of samples per time-unit as `fs`. In the same units, an
	`offset` and a `refractory` period can be specified. The offset
	dictates when each epoch starts relative to the nominal start index.
	If `refractory` is > 0, a slice will not be recorded if its start
	index occurs closer to the previous start index than this
	(the `refrac()` function is called internally to achieve this).
	
	Slices that would extend beyond the end of `x` are not returned,
	unless `return_partial` is set to True (in which case you cannot
	also set `return_array` to True).
	"""
	# uses: numpy, refrac()
	out = []
	if return_array and return_partial: raise ValueError( 'the return_array and return_partial options cannot both be set to True' )
	length_samples = int( 0.5 + float( fs ) * length )
	offset_samples = int( 0.5 + float( fs ) * offset )
	if not isinstance( x, numpy.ndarray ): x = numpy.asarray( x )
	sub = [ slice( None ) for i in x.shape ]
	start_indices = numpy.asarray( start_indices ).ravel().tolist()
	start_indices = refrac( start_indices, interval=refractory, fs=fs ) # even if refractory=0, this also wrangles the type/shape of start_indices as necessary
	indices_used = []
	timebase = ( numpy.arange( float( length_samples ) ) + offset_samples ) / float( fs )
	for ind in start_indices:
		start = ind + offset_samples
		stop = start + length_samples
		sub[ axis ] = slice( max( 0, start ), stop )
		epoch = x[ tuple( sub ) ]
		if epoch.shape[ axis ] == length_samples or return_partial:
			out.append( epoch )
			indices_used.append( ind )
	if return_array: out = numpy.array( out )
	return out, timebase, indices_used

def match_events( base_indices, candidate_indices, min_offset=None, max_offset=0, fs=1.0, mode='closest' ):
	"""
	For each index in `base_indices`, return the closest matching index
	in `candidate_indices`. Each candidate index can only be used once.
	A candidate will only be considered if its offset, relative to the
	base, complies with the specified `min_offset` and `max_offset` (if
	specified).  By default `min_offset` and `max_offset` are expressed
	in the same units as the indices (let's assume that's "samples"),
	but you can express them in more natural time-units if you use `fs`
	to specify the number of samples per time-unit.
	
	The default setting `max_offset=0` ensures that a candidate event
	can only be matched to a base event if it was coincident with, or
	happened earlier than, the base event. 
	
	The function returns a list the same length as `base_indices`.
	Its items are either members of `candidate_indices`, or `None`
	where a match could not be found.
	
	A typical use-case for this function is when you have stimulus events
	whose "time zero" are defined by hardware trigger pulses, and you want
	to query the value of a state variable corresponding to each stimulus
	event. The state variable, however, represents the software's
	*intention* to deliver a particular stimulus, which occurs (and is
	recorded) somewhat earlier than the pulse, the latter being triggered
	by the physics of stimulus delivery and subject to delay by the
	system's audio or video lag. So, for example, you might do::
	
	    hardwareEventIndices = events(states['DigitalInput1'])
	    softwareEventIndices = events(states['StimulusCode'])
	    
	    softwareEventIndices = match_events(hardwareEventIndices, softwareEventIndices)
	    
	    # NB: softwareEventIndices will now contain `None` wherever a match could not
	    #     be made, so you may wish to implement special handling to avoid an
	    #     exception in the next line:
	    
	    stimulusCodes = states['StimulusCode'].flat[ softwareEventIndices ]
	    
	    # stimulusCodes now contains one non-zero stimulus code per
	    # corresponding hardware event
	
	"""
	min_offset = float( '-inf' ) if min_offset is None else min_offset * fs
	max_offset = float( '+inf' ) if max_offset is None else max_offset * fs
	if min_offset > max_offset: raise ValueError( 'min_offset cannot be greater than max_offset (it can be negative)' )
	
	candidate_indices = set( candidate_indices )
	matched = []
	for base_index in base_indices:
		close_enough = [ candidate_index for candidate_index in candidate_indices if min_offset <= ( candidate_index - base_index ) <= max_offset ]
		if close_enough:
			if   mode == 'closest':  key = lambda candidate_index: ( abs( candidate_index - base_index ), candidate_index )
			elif mode == 'earliest': key = lambda candidate_index:  candidate_index
			elif mode == 'latest':   key = lambda candidate_index: -candidate_index
			else: raise ValueError( 'unrecognized mode' )
			closest = min( close_enough, key=key )
			candidate_indices.remove( closest )
		else:
			closest = None
		matched.append( closest )
	return matched
	