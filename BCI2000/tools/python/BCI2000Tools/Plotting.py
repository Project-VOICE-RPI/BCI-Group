# -*- coding: utf-8 -*-

# ///////////////////////////////////////////////////////////////////////////
# $Id: Plotting.py 8212 2024-06-20 22:26:13Z jhill $
# Author: jeremy.hill@neurotechcenter.org
# Description: graphical helper functions (matplotlib wrappers)
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
	'load_plt', 'finish_plt',
	'clear_axes', 'plot',
	'imagesc', 'scatterplot', 'scatcmp', 'stem', 'bar',
	'colorbar', 'rmcolorbar',
	'make_cmap', 'transform_cmap', 'show_cmaps',
	'subplots',
	'curve',
	'cax',
	'indicate',
	'superimpose', 'look', 'hotfig', 'clickplots',
	'savepdf', 
	'resolve_figure', 'resolve_axes',
	'closefigs',
	'AX',
]

import sys

import numpy

if sys.version < '3': bytes = str
else: unicode = str; basestring = ( unicode, bytes )

def load_plt():
	first_time = 'matplotlib.pyplot' not in sys.modules
	try:
		import matplotlib
		set_interactive = ('matplotlib.backends' not in sys.modules and 'IPython' in sys.modules)
		if set_interactive: matplotlib.interactive(True)
		import matplotlib.pyplot as plt
	except:
		print( __name__ + " module failed to import matplotlib.pyplot: plotting methods will not work" )
	else:
		if set_interactive and hasattr(plt, 'ion'): plt.ion()
		if first_time: import warnings; warnings.filterwarnings( action='ignore', message='unclosed event loop' )
		return plt
		
def finish_plt( focus=False ):
	if focus: look()
	plt = load_plt()
	if plt.rcParams[ 'interactive' ] or 'IPython' in sys.modules: plt.draw()
	else: plt.show()

def project(a, maxdim):
	"""
	Return a view of the numpy array `a` that has at least `maxdim+1`
	dimensions.
	"""
	if isinstance(a, numpy.matrix) and maxdim > 1: a = numpy.asarray(a)
	else: a = a.view()
	a.shape += type( a.shape )( (1,) * (maxdim-len(a.shape)+1) )
	return a

def filterdict(d, exact=(), startswith=None, endswith=None):
	f = dict([(k,v) for k,v in d.items() if k in exact or (startswith is not None and k.startswith(startswith)) or (endswith is not None and k.endswith(endswith))])
	for k in f: d.pop(k)
	return f

def plot(*pargs,**kwargs):
	"""
	A wrapper around plt.plot that reduces dimensionality-related fiddliness::
	
	    plot(x, y)
	    plot(y)
	
	where either `x` or `y`, independent of each other, can specify multiple
	lines.
	
	Additional options and their defaults::
	
		axis = 0         Along which dimension can one step while staying on
		                 the same graphical line?
		stem = False     If True, do a stem plot instead of an ordinary line
		grid = True      Whether to turn on the grid.
		balance = None   If None, do nothing. If a numeric value, balance the
		                 y axis limits around this value.
		aspect = None    If 'auto', 'image' or 'equal', apply that aspect mode
		hold = False     If False, clear the axes before plotting.
		drawnow = True   If True, execute plt.draw() after plotting.
	"""
	hold = kwargs.pop('hold', False)
	axis = kwargs.pop('axis', 0)
	drawnow = kwargs.pop('drawnow', True)
	grid = kwargs.pop('grid', True)
	balance = kwargs.pop('balance', None)
	stem = kwargs.pop('stem', False)
	aspect = kwargs.pop('aspect', None)
	axkwargs = filterdict(kwargs, ['title', 'xlabel', 'ylabel', 'ylim', 'xlim'])

	pargs = list(pargs) # makes a copy, at least of the list container
	allvec = True
	for i in range(len(pargs)):
		if isinstance(pargs[i], (tuple,list)):
			pargs[i] = numpy.array(pargs[i],dtype=numpy.float64)
		if isinstance(pargs[i], numpy.ndarray):
			allvec &= (max(pargs[i].shape) == numpy.prod(pargs[i].shape))
			if len(pargs[i].shape) > 1:
				pargs[i] = project(pargs[i],axis).swapaxes(0,axis)
			isinf = numpy.isinf(pargs[i])
			if numpy.any(isinf):
				pargs[i] = pargs[i].copy()
				pargs[i][isinf] = numpy.nan # crude workaround---plt.plot can't cope with infinite values
	if allvec:
		for i in range(len(pargs)):
			if isinstance(pargs[i], numpy.matrix):  pargs[i] = pargs[i].A
			if isinstance(pargs[i], numpy.ndarray): pargs[i] = pargs[i].flatten()	
	pargs = tuple(pargs)

	plt = load_plt()
	axes = resolve_axes( axes=kwargs.pop( 'axes', None ), figure=kwargs.pop( 'figure', None ), sca=kwargs.pop( 'sca', False ) )
	if not hold: clear_axes( axes )
	
	if stem:
		if len(pargs) == 1: pargs = (range(pargs[0].shape[axis]),) + pargs
		p = axes.stem(*pargs, **kwargs)
		x = pargs[0]
		xl = numpy.r_[float(x[0]), float(x[-1])]
		if len(x) == 1: xl += [-0.5, 0.5]
		else: xl += numpy.r_[float(x[0]-x[1]), float(x[-1]-x[-2])] / 2.0
		axes.set_xlim(xl)
	else:
		p = axes.plot(*pargs,**kwargs)
	axes.grid(grid)
	if balance is not None:
		yl = numpy.array(axes.get_ylim())
		yl = balance + numpy.array([-1,+1]) * max(abs(yl - balance))
		axes.set_ylim(yl)
	if aspect is not None: axes.set_aspect({'image':'equal'}.get(aspect, aspect))
	axes.set(**axkwargs)
	if drawnow: axes.figure.canvas.draw_idle()
	return p
	
def clear_axes( axes=None, removeColorbar=True ):
	"""
	Remove a few known hangovers before clearing the axes with `cla()`.
	"""
	plt = load_plt()
	if axes is None: axes = plt.gcf()
	if isinstance( axes, plt.Figure ): axes = axes.gca()
	axes.set_aspect('auto') # image aspect ratio
	axes.set_ylim(sorted(axes.get_ylim())) # ydir reversed
	if removeColorbar: rmcolorbar(axes, drawnow=False) # colorbar
	axes.cla()

def imagesc(img, x=None, y=None, axes=None, hold=False, drawnow=True, aspect='image', balance=None, colorbar=False, grid=False, ydir='reverse', **kwargs):
	kwargs['interpolation'] = kwargs.get('interpolation', 'nearest')
	kwargs['cmap'] = kwargs.get('cmap', 'kelvin_i')
	cbkwargs = filterdict(kwargs, startswith='colorbar')
	cbkwargs = dict([(k[len('colorbar'):],v) for k,v in cbkwargs.items()])
	axlabelkwargs = filterdict(kwargs, ['title', 'xlabel', 'ylabel'])
	auto_aspect = {'equal':False, 'image':False, 'auto':True}.get(aspect)
	if auto_aspect is None: raise ValueError('aspect should be "image" or "auto"')
	plt = load_plt()
	axes = resolve_axes( axes=axes, figure=kwargs.pop( 'figure', None ), sca=kwargs.pop( 'sca', False ) )
	if not hold: clear_axes( axes, removeColorbar=not colorbar )
	
	img = numpy.asarray(img)

	xlab,ylab = None,None
	if isinstance(x, (tuple,list,numpy.ndarray)) and isinstance(x[0], basestring): xlab,x = x,None
	if isinstance(y, (tuple,list,numpy.ndarray)) and isinstance(y[0], basestring): ylab,y = y,None
	if x is None: x = numpy.arange(img.shape[1], dtype=numpy.float64)
	if y is None: y = numpy.arange(img.shape[0], dtype=numpy.float64)
	x = numpy.asarray(x).flatten()
	y = numpy.asarray(y).flatten()
	if len(x) == 1: xl = [ x[ 0 ] - 0.5, x[ 0 ] + 0.5 ]	
	else: xl = [x[0] - 0.5 * (x[1]-x[0]),   x[-1] + 0.5 * (x[-1]-x[-2])]
	if len(y) == 1: yl = [ y[ 0 ] - 0.5, y[ 0 ] + 0.5 ]	
	else: yl = [y[0] - 0.5 * (y[1]-y[0]),   y[-1] + 0.5 * (y[-1]-y[-2])]
	tol = 1e-10
	regular = ( len(x) == 1 or (numpy.diff(x).ptp() < tol) ) and ( len(y) == 1 or (numpy.diff(y).ptp() < tol) )
	if ydir == 'reverse': yl = yl[::-1]; origin='upper'
	else: origin='lower'
	if not regular: raise ValueError('x and y data must be regularly spaced') # NonUniformImage just doesn't play nice, with ydir or with clim scaling
	h = axes.imshow(img, extent=xl+yl, origin=origin, **kwargs)		
	if xlab is not None: axes.set_xticks(x); axes.set_xticklabels(list(xlab))
	if ylab is not None: axes.set_yticks(y); axes.set_yticklabels(list(ylab))
	if auto_aspect: axes.set_aspect('auto')
	else: axes.set_aspect('equal')
	axes.grid(grid)
	axes.set_xlim(xl)
	axes.set_ylim(yl)
	axes.set(**axlabelkwargs)
	if balance is not None:
		c = numpy.array(h.get_clim())
		c = balance + numpy.array([-1,+1]) * max(abs(c - balance))
		h.set_clim(c)
	if colorbar: _colorbar(parent_axes=axes, **cbkwargs)
	else: rmcolorbar(parent_axes=axes)
	if drawnow: axes.figure.canvas.draw_idle()
	return h

def scatterplot(*pargs, **kwargs):
	"""
	scatterplot(xy)         # scatterplots xy[:,1].flat against xy[:,0].flat
	scatterplot(xy1, 'r*')
	scatterplot(xy1, 'r*', xy2, 'bs')
	scatterplot(xy1, 'r*', xy2, 'bs', markersize=10, hold=False, drawnow=True)
	
	scatterplot(x, y)      # scatterplots y.flat against x.flat
	scatterplot(x1, y1, 'r*')
	scatterplot(x1, y1, 'r*', x2, y2, 'bs')
	scatterplot(x1, y1, 'r*', x2, y2, 'bs', markersize=10, hold=False, drawnow=True)
	"""
	x = None
	y = None
	plotargs = []
	connected = []
	if not isinstance(pargs[-1], basestring):
		pargs = list(pargs) + ['*']
	for i,arg in enumerate(pargs):
		if isinstance(arg, basestring):
			if y is None:
				if max( x.shape ) == x.size: x, y = numpy.arange( x.size ), x.flatten()
				else: x,y = x[:, 0], x[:, 1]
			plotargs += [ x.ravel(), y.ravel(), arg ]
			connected.append('-' in arg)
			x = y = None
		elif x is None: x = numpy.asarray( arg )
		elif y is None: y = numpy.asarray( arg )
	h = plot(*plotargs, **kwargs)
	for hi in zip(h, connected):
		if not connected: hi.set_linestyle('None')
	return h
	
def scatcmp(a, b, hold=False, drawnow=True, markerorder=None, **kwargs):
	kwargs['linestyle'] = kwargs.get('linestyle', 'None')
	grid = kwargs.pop('grid', True)
	grid = {'on':True, 'off':False}.get(grid,grid)
	h = plot(a, b, drawnow=False, hold=hold, **kwargs)
	import matplotlib
	if 'marker' not in kwargs:
		if markerorder is None:
			mm = matplotlib.lines.lineMarkers
			keyfn = lambda x: 0 if x is None else x
			markerorder = sorted([m for m in mm if isinstance(m, basestring) and len(m.strip())], key=keyfn) + sorted([m for m in mm if not isinstance(m, basestring)], key=keyfn)
		for i,hi in enumerate(h): hi.set_marker(markerorder[i % len(markerorder)])
	axes = h[ 0 ].axes
	lim = axes.get_xlim() + axes.get_ylim()
	lim = (min(lim),max(lim))
	axes.set_xlim(lim)
	axes.set_ylim(lim)
	axes.grid(grid)
	axes.plot(lim, lim, linestyle='-', color=(0.6,0.6,0.6), scalex=False, scaley=False)
	if drawnow: axes.figure.canvas.draw_idle()
	return h

def stem(*pargs, **kwargs):
	kwargs['stem'] = True
	return plot(*pargs, **kwargs)


def colorbar(mappable=None, parent_axes=None, **kwargs):
	"""
	Create a colorbar in such a way that it can be found again and reused, or removed.
	Or, if one already exists associated with the specified parent_axes, use and
	update the existing one.  Use `rmcolorbar()` to remove.  matplotlib, y u no do this?
	
	`mappable` is the handle to the image, patch or surface that is being described.
	If in the case of a single image on a given axes, it may be found automatically and
	you can omit the argument, but if the `mappable` object is a non-image or not the
	current image on the axes, you should pass this explicitly.
	"""
	plt = load_plt()
	if mappable is None:
		if parent_axes is None: mappable = plt.gci()
		else: mappable = parent_axes.get_images()[-1]  # NB: doesn't find patch, surf, etc - only images. So to use this with non-images, supply the handle explicitly instead of relying on gca()
	ax = parent_axes
	if ax is None:
		try: ax = mappable.get_axes()
		except: ax = mappable.axes
	cb = getattr(ax, 'colorbar', None)
	if cb is None:
		kwargs['ax'] = ax
		try: ax.oldposition = ax.get_position( original=True )
		except: ax.oldposition = ax.get_position()
		try: ax.oldanchor = ax.get_anchor()
		except: pass
	else:
		kwargs['cax'] = cb.ax
		cb.ax.cla()
	title = kwargs.pop('title', None)
	ax.colorbar = plt.colorbar(mappable, **kwargs)
	if title is not None: ax.colorbar.ax.set_title(title)
	plt.draw()
	return ax.colorbar
_colorbar = colorbar

def rmcolorbar(parent_axes=None, drawnow=True):
	"""
	Remove a colorbar created with `colorbar()` from this module
	"""
	plt = load_plt()
	ax = parent_axes
	if ax is None: ax = plt.gca()
	cb = getattr(ax, 'colorbar', None)
	if cb is None: return
	try: cb.remove()
	except: pass
	try: cb.ax.get_figure().delaxes(cb.ax)
	except: pass
	ax.colorbar = cb = None
	if getattr(ax, 'oldposition', None) is not None:
		try: ax.set_position(ax.oldposition, which='both')
		except: ax.set_position(ax.oldposition)
	if getattr(ax, 'oldanchor', None) is not None:
		ax.set_anchor( ax.oldanchor )
	if drawnow: plt.draw()

def make_cmap(cmap, name, n=256):
	plt = load_plt(); import matplotlib
	cmap = matplotlib.colors.LinearSegmentedColormap(name, cmap, n)
	if name not in plt.colormaps():
		try:
			try: matplotlib.colormaps.register
			except: matplotlib.cm.register_cmap(name=name, cmap=cmap)
			else: matplotlib.colormaps.register(name=name, cmap=cmap)
		except: print( "failed to register colormap '%s'" % name )
			
	return cmap

def transform_cmap(cmap, name=None, n=256, reverse=False, complement=False):
	plt = load_plt()
	if isinstance(cmap, basestring): cmap = get_cmap(cmap)
	cmap = getattr(cmap, '_segmentdata', cmap)
	out = {}
	for k in ('red', 'green', 'blue'):
		v = numpy.array(cmap[k])
		if complement: v[:, 1:] = 1.0 - v[:, 1:]
		if reverse:    v[:, 1:] = v[::-1, 1:]
		out[k] = v
	if name is not None: out = make_cmap(out, name=name, n=n)
	return out

def get_cmap( name ):
	plt = load_plt()
	try: plt.colormaps.get
	except: return plt.cm.get_cmap(name)
	else: return plt.colormaps.get(name)

def show_cmaps(*pargs):
	plt = load_plt()
	cmaps = []
	for arg in pargs:
		if isinstance(arg, basestring): arg = arg.split()
		if isinstance(arg, (tuple,list)): cmaps += arg
		else: cmaps.append(arg)
	try: cmap_d = plt.colormaps
	except: cmap_d = plt.cm.cmap_d
	if len(cmaps) == 0: cmaps=sorted([m for m in cmap_d if not m.endswith("_r")])
	plt.clf()
	for i,cmap in enumerate(cmaps):
		plt.subplot(len(cmaps), 1, i+1)
		if isinstance(cmap, basestring): cmap = get_cmap(cmap)
		plt.imshow([numpy.linspace(0.0,1.0,256,endpoint=True)], cmap=cmap)
		plt.gca().set(aspect='auto', yticks=[0.0], yticklabels=[cmap.name])
	plt.draw()

def subplots(r, c=None, fig=None, **kwargs):
	plt = load_plt()
	if fig is None: fig = plt.gcf()
	if c is None:
		if isinstance(r, int):
			nPlots = r
			ar = fig.get_size_inches()
			ar = float(ar[0])/float(ar[1])
			layout = numpy.r_[nPlots/ar, nPlots*ar] ** 0.5
			i = numpy.argmin(abs(layout - numpy.round(layout)))
			r = int(round(layout[i]))
			c = int(numpy.ceil(nPlots/float(r)))
			if i == 1: r,c = c,r
			while r * (c-1) >= nPlots: c -= 1
			while (r-1) * c >= nPlots: r -= 1
		else:
			r,c = r
	i = 0
	ax = []
	for ri in range(r):
		row = []; ax.append(row)
		for ci in range(c):
			row.append(plt.subplot(r, c, i+1, **kwargs))
			i += 1
	return numpy.array(ax)
	
def make_kelvin():
	kelvin_i = {
		'red': (
			(0.000, 0.0, 0.0, ),
			(0.350, 0.0, 0.0, ),
			(0.500, 1.0, 1.0, ),
			(0.890, 1.0, 1.0, ),
			(1.000, 0.5, 0.5, ),
		),
		'green': (
			(0.000, 0.0, 0.0, ),
			(0.125, 0.0, 0.0, ),
			(0.375, 1.0, 1.0, ),
			(0.640, 1.0, 1.0, ),
			(0.910, 0.0, 0.0, ),
			(1.000, 0.0, 0.0, ),
		),
		'blue': (
			(0.000, 0.5, 0.5, ),
			(0.110, 1.0, 1.0, ),
			(0.500, 1.0, 1.0, ),
			(0.650, 0.0, 0.0, ),
			(1.000, 0.0, 0.0, ),
		),
	}
	kelvin_i = make_cmap(kelvin_i, 'kelvin_i', 256)
	kelvin_r = transform_cmap(kelvin_i, 'kelvin_r', 256, complement=True)
	kelvin   = transform_cmap(kelvin_i, 'kelvin',   256, complement=True, reverse=True)

make_kelvin()

def curve(x,y=None, hold=False, drawnow=True, **kwargs):
	plt = load_plt(); import matplotlib, matplotlib.path
	axes = resolve_axes( axes=kwargs.pop( 'axes', None ), figure=kwargs.pop( 'figure', None ), sca=kwargs.pop( 'sca', False ) )
	if not hold: clear_axes( axes )
	kwargs['facecolor'] = kwargs.get('facecolor', 'None')
	if y is None: xy = x
	else: xy = numpy.c_[x,y]
	codes = [matplotlib.path.Path.MOVETO] + [matplotlib.path.Path.CURVE4] * (len(xy)-1)
	path = matplotlib.path.Path(xy,codes)
	patch = matplotlib.patches.PathPatch(path, lw=2, **kwargs)
	axes.add_patch(patch)
	if drawnow: plt.draw()

def cax( handles=None, whichAx='c', lim=None, min=None, max=None, include=None, common=False, balance=None, midpoint=None, auto=False ):
	plt = load_plt()
	
	def search_handles( handles, reclevel=0 ):
		out = []
		if reclevel >= 10: zark # allows `debug` of apparent indefinite recursion
		try: handles = list( handles )
		except: handles = [ handles ]
		for h in handles:
			if isinstance( h, ( int, float ) ):
				if h == 0: h = plt.get_fignums()
				elif plt.fignum_exists( h ): h = plt.figure( h )
			while hasattr( h, 'axes' ) and h.axes is not h: h = h.axes   # this was intended to grab the children of a figure, but it can also grab the parent of an AxesImage....
			try: h = list( h )
			except: out.append( h )
			else: out.extend( search_handles( h, reclevel=reclevel+1 ) )
		return out
	if   isinstance( handles, str ) and handles == 'gca': handles = plt.gca()
	elif isinstance( handles, str ) and handles == 'gcf': handles = plt.gcf()
	elif handles is None: handles = plt.gcf()
	handles = search_handles( handles )
	if whichAx == 'c': handles = sum( [ list( ax.images ) for ax in handles ], [] )  #... with the unintended side-effect that if you pass an AxesImage handle, the function will affect it and any of its siblings on the same axes
	
	all = []
	
	for handle in handles:
		getter = getattr( handle, 'get_' + whichAx + 'lim' )
		setter = getattr( handle, 'set_' + whichAx + 'lim' )
		if auto:
			if whichAx == 'c': handle.autoscale()
			else: handle.autoscale( enable=True, axis=whichAx, tight=True )
		v = list( getter() )
		if lim is not None: v = [ numpy.min( lim ), numpy.max( lim ) ]
		if min is not None: v[ 0 ] = min
		if max is not None: v[ 1 ] = max
		if include is not None:
			v = v + numpy.asarray( include ).ravel().tolist();
			v = [ numpy.min( v ), numpy.max( v ) ]
		if balance and midpoint is None: midpoint = 0.0
		if balance == False: midpoint = None
		if midpoint is not None:
			hw = numpy.max( [ abs( x - midpoint ) for x in v ] )
			v = [ midpoint - hw, midpoint + hw ]
		setter( v )
		all.extend( v )
		
	if common:
		v = [ numpy.min( all ), numpy.max( all ) ]
		for handle in handles:
			setter = getattr( handle, 'set_' + whichAx + 'lim' )
			setter( v )
	plt.draw()

def indicate( dataXY, textXY=( 0, 0 ), text='', xycoords='data', textcoords='figure fraction', axes=None, **kwargs ):
	"""
	Wraps `plt.annotate()` to be somewhat easier to use and have
	nicer defaults.
	
	`textXY` is in figure-fraction coordinates by default (same as
	passing `axes.figure.transFigure`).
	
	You can use `arrowprops` if you want, but you can also change
	individual properties in `**kwargs` by prefixing the keyword
	names with `arrow`.  Text property names may optionally be
	prefixed with `text`.
		
	As with `plt.annotate()`, the returned handle is an instance of
	`Annotation`, which is a subclass of `Text` that carries a handle
	to the arrow patch in its `.arrow_patch` attribute.
	
	Example::
	
	    indicate( [0.25,0.75], [0, 1], va='top', text='LOOK\nHERE!', arrowcolor='r')
	    
	"""
	plt = load_plt()
	axes = resolve_axes( axes=axes, figure=kwargs.pop( 'figure', None ), sca=kwargs.pop( 'sca', False ) )
	arrowprops = dict( kwargs.pop( 'arrowprops', dict(
		ec='none', width=10, alpha=0.75, # nicer defaults
	) ) )
	arrowprops.update( {
		k[ 5: ].lstrip( '_' ) : kwargs.pop( k )
		for k in list( kwargs )
		if k.startswith( 'arrow' )
	} )
	if 'width'     in arrowprops: arrowprops.setdefault( 'headwidth',  arrowprops[ 'width'     ] * 1.618 ** 2 )
	if 'headwidth' in arrowprops: arrowprops.setdefault( 'headlength', arrowprops[ 'headwidth' ] * 1.618 )
	textprops = {
		( k[ 4: ].lstrip( '_' ) if k.startswith( 'text' ) else k ) : v
		for k, v in kwargs.items()
	}
	textprops.setdefault( 'fontsize', 20 )
	h = axes.annotate( text, xy=dataXY, xytext=textXY, xycoords=xycoords, textcoords=textcoords, arrowprops=arrowprops, **textprops )
	return h
	
def bar( x, y, yerr=None, axes=None, hold=False, ygrid=False, ylim=None, title=None, xlabel=None, ylabel=None, **kwargs ):
	"""
	`x` is a list of M x-tick labels. They may be numeric, but the numeric distances 
	between them will not be respected: they are just treated as labels for
	uniformly-spaced ticks on the x-axis.
	
	`y` may be an array of M values, or an M-by-N array encoding N separate data series.
	The data series will be plotted side-by-side in grouped bars---this is the reason for
	this functions's existence as distinct from `plt.bar()`.
	
	`yerr`, if not equal to `None`, may be the same shape as `y`, or it may be a two-
	element sequence of arrays `(lower, upper)` where each of the constituents, `lower`
	and `upper`, has the same shape as `y`.  
	
	To make the error-bar caps visible, pass a non-zero `capsize`.
	"""
	plt = load_plt()
	axes = resolve_axes( axes=axes, figure=kwargs.pop( 'figure', None ), sca=kwargs.pop( 'sca', False ) )
	y = numpy.asarray( y, dtype=float )
	if yerr is not None:
		yerr = numpy.asarray( yerr, dtype=float )
		if tuple( yerr.shape ) == ( 2, ) + tuple( y.shape ):
			lower, upper = yerr
		else:
			while yerr.ndim < 2: yerr = yerr[ :, None ]		
			lower = upper = yerr
	while y.ndim < 2: y = y[ :, None ]
	if yerr is not None and tuple( lower.shape ) != tuple( y.shape ): raise ValueError( "y and yerr have incompatible shapes" )
	nLocations, nSeries = y.shape
	if x is None: x = numpy.arange( nLocations )
	x = numpy.asarray( x, dtype=object ).ravel().tolist()
	if len( x ) != nLocations: raise ValueError( "x and y have incompatible dimensions" )
	xloc = numpy.arange( nLocations )	
	if not hold: axes.cla()
	width = 1.0 / ( nSeries + 1.0 )
	offset = -0.5 * ( nSeries - 1.0 ) * width
	handles = []
	for iSeries, yi in enumerate( y.T ):
		if yerr is None: yerri = None
		else: yerri = numpy.concatenate( [ lower[ :, [ iSeries ] ], upper[ :, [ iSeries ] ] ], axis=1 ).T
		handles.append( axes.bar( xloc + offset + iSeries * width, yi, yerr=yerri, width=width, **kwargs ) )
	axes.set( xticks=xloc, xticklabels=x )
	axes.yaxis.grid( ygrid )
	if title is not None: axes.set_title( title )
	if xlabel is not None: axes.set_xlabel( xlabel )
	if ylabel is not None: axes.set_ylabel( ylabel )
	if ylim is not None: axes.set_ylim( ylim )
	return handles

def superimpose( figs='all' ):
	plt = load_plt()
	if figs == 'all': figs = plt.get_fignums()
	if not isinstance( figs, ( tuple, list ) ): figs = [ figs ]
	figs = list( figs )
	for i, f in enumerate( figs ):
		if isinstance( f, int ): figs[ i ] = plt.figure( f )
	geom = figs[ 0 ].canvas.manager.window.geometry()
	for fig in figs[ 1: ]: fig.canvas.manager.window.geometry( geom )
	plt.draw()

def look( fig=None ):
	plt = load_plt()
	if fig is None and len( plt.get_fignums() ): fig = plt.gcf()
	if fig is None: sys.stderr.write( 'there are no open figures to look at\n' ); return
	if isinstance( fig, int ): fig = plt.figure( fig )
	try: fig.canvas.manager.show()
	except: pass
	else: return
	try: fig.canvas._tkcanvas.focus_force() # requires   matplotlib.use('tkagg')
	except: pass
	else: return
	try: fig.canvas.manager.window.focus_force() # older matplotlib, qtagg; works but then removes focus from whichever part of the figure is listening to keystrokes :-(
	except: pass
	else: return

def hotfig( figs='all', align=False ):
	plt = load_plt()
	if figs == 'all': figs = plt.get_fignums()
	if not isinstance( figs, ( tuple, list ) ): figs = [ figs ]
	figs = list( figs )
	for i, f in enumerate( figs ):
		if isinstance( f, int ): figs[ i ] = plt.figure( f )
	if align == True: align = figs
	if align: superimpose( align )
	def kp(event):
		memoryField = '_hotfig'
		if not isinstance( event.key, basestring ): return
		key = event.key.lower()
		if key.startswith( 'alt+' ): key = key[ 4: ]
		codes = list( '1234567890QWERTYUIOP'.lower() )
		if key in codes: target = int( codes.index( key ) ) + 1
		elif key in '[]':
			direction = -1 if key == '[' else +1
			activeFigure = event.canvas.figure
			remembered = getattr( plt, memoryField, None )
			if remembered is not None and plt.fignum_exists( remembered ):
				activeFigure = plt.figure( remembered )
			target = activeFigure.number + direction
			family = sorted( activeFigure._hotfig[ 'family' ] )
			while target:
				if not ( family[ 0 ] <= target <= family[ -1 ] ): target = None
				elif plt.fignum_exists( target ) and target in family: break
				else: target += direction
		else: target = None
		if target and plt.fignum_exists( target ):
			setattr( plt, memoryField, target )
			look( target )
		
	for fig in figs:
		previous = getattr( fig, '_hotfig', {} )
		if previous: fig.canvas.mpl_disconnect( previous[ 'connectionID' ] )
		fig._hotfig = dict(
			connectionID = fig.canvas.mpl_connect( 'key_press_event', kp ),
			family = [ f.number for f in figs ],
		)
	look()
	
def clickplots( fig=None, on=True ):
	reconnect( fig, '_clickplotsConnectionID', 'button_press_event', ToggleSubplotZoom if on else None )

def reconnect( fig, attrName, eventType, callback ):
	plt = load_plt()
	if fig is None: fig = plt.gcf()
	previousID = getattr( fig, attrName, None )
	if previousID is not None: fig.canvas.mpl_disconnect( previousID )
	if eventType is not None and callback is not None:
		setattr( fig, attrName, fig.canvas.mpl_connect( eventType, callback ) )
	
def ToggleSubplotZoom( x ):
	plt = load_plt()
	attrName = '_clickplotsUndoList'
	import sys; sys._event = x  #for debugging only
	
	if hasattr( x, 'inaxes' ):
		fig = x.canvas.figure
		targetAxes = fig.gca() if fig.axes and hasattr( fig, attrName ) else x.inaxes
	elif hasattr( x, 'figure' ):
		targetAxes = x
		fig = targetAxes.figure
	else:
		fig = x
		targetAxes = fig.gca() if fig.axes and hasattr( fig, attrName ) else None
			
	if targetAxes is None: return
	undo = fig.__dict__.pop( attrName, None )
	fig.sca( targetAxes )
	original = False
	def GetPosition( ax ): return ax.get_position() # original=original )
	def SetPosition( ax, p ): return ax.set_position( p )#, which='original' if original else 'active' )
	colorbarAxes = [ cb.patch.axes for h in plt.findobj( targetAxes ) for cb in [ getattr( h, 'colorbar', None ) ] if cb ]
	if undo is None:
		undo = []
		setattr( fig, attrName, undo )
		for ax in fig.axes:
			def f( ax=ax, position=GetPosition( ax ), visible=ax.get_visible(), anchor=ax.get_anchor() ):
				SetPosition( ax, position )
				ax.set( visible=visible, anchor=anchor )
			undo.append( f )
			if ax in colorbarAxes: continue
			ax.set( visible=False )
		# TODO: how to adjust the position of targetAxes and each colorbarAxes so that
		#       (a) they have the same spatial relationship between their anchors as they did before, and
		#       (b) they *collectively* fill the figure
		#SetPosition( targetAxes, [ 0, 0, 1, 1 ] )
		SetPosition( targetAxes, [ fig.subplotpars.left, fig.subplotpars.bottom, fig.subplotpars.right - fig.subplotpars.left, fig.subplotpars.top - fig.subplotpars.bottom ] )
		targetAxes.set( visible=True, anchor='C' )
	else:
		for x in undo: x()
	fig.canvas.draw_idle()

def savepdf( filename, figures='all' ):
	plt = load_plt()
	if figures == 'all': figures = plt.get_fignums()
	if not isinstance( figures, ( tuple, list ) ): figures = [ figures ]
	from matplotlib.backends.backend_pdf import PdfPages
	with PdfPages( filename ) as pdf:
		for figure in figures: pdf.savefig( figure )


def resolve_figure( figure=None, figsize=None, clf=False, scf=False, **otherNewFigureProperties ):
	"""
	This allows you to create custom plotting functions in which the user can specify where
	to plot: the user can supply a Figure instance, a figure number, the string `'new'` to
	explicitly demand a new figure, or `None` to use the current figure (opening a new figure
	if necessary). At the same, your function has control over the size of any new figure that
	may be opened.
	
	Example::
	
		def MyPlot(x, y, figure=None):
			figure = resolve_figure( figure, [5, 5] )
			figure.gca().plot( x, y )
	
	Additionally, your function can pass `clf=True` to clear the figure, and/or `scf=True`
	to make it the current figure in the pyplot state machine.
	
	`figsize`, if supplied, should be `[widthInInches, heightInInches]` (this property
	is initialized with the `figsize` argument when opening the figure, and may not be
	mutable thereafter; it can be read from an existing figure via
	`widthInInches, heightInInches = figure.get_size_inches()`.

	For even more precise control, use `resolve_axes()`.
	"""
	newFigureProperties = dict()
	if figsize: newFigureProperties[ 'figsize' ] = figsize
	newFigureProperties.update( otherNewFigureProperties )
	
	plt = load_plt()
	if isinstance( figure, int ): figure = plt.figure( figure, **newFigureProperties )
	if figure is None and plt.get_fignums(): figure = plt.gcf()
	if figure is None or figure == 'new': figure = plt.figure( **newFigureProperties )
	if clf: figure.clf()
	if scf: plt.figure( figure.number )
	return figure

def resolve_axes( axes=None, figure=None, figsize=None, cla=False, sca=False, **otherNewFigureProperties ):
	"""
	This allows you to create custom plotting functions in which the user can specify where
	to plot: the user can supply an Axes instance, a Figure instance, a figure number, the
	string `'new'` to explicitly demand a new figure, or `None` to use the current axes
	(opening a new figure if necessary). At the same, your function has control over the
	size of any new figure that may be opened.
	
	Example::
	
		def MyPlot(x, y, axes=None, figure=None):
			axes = resolve_axes( axes, figure, [5, 5] )
			axes.plot( x, y )

	Additionally, your function can pass `cla=True` to clear the axes, and/or `sca=True`
	to make it the current axes in the pyplot state machine.
	
	`figsize`, if supplied, should be `[widthInInches, heightInInches]` (this property
	is initialized with the `figsize` argument when opening the figure, and may not be
	mutable thereafter; it can be read from an existing figure via
	`widthInInches, heightInInches = figure.get_size_inches()`.
	
	See also `resolve_figure()`.
	"""
	# figure = plt.figure( figsize=[ widthInInches, heightInInches ] )   # figsize   to set
	# widthInInches, heightInInches = figure.get_size_inches()           # get_size_inches() to get
	newFigureProperties = dict()
	if figsize: newFigureProperties[ 'figsize' ] = figsize
	newFigureProperties.update( otherNewFigureProperties )
	
	plt = load_plt()
	mustOpenNewFigure = ( axes is None and figure == 'new' )
	if mustOpenNewFigure: figure = None
	if axes is None: axes = figure
	if isinstance( axes, int ): axes = plt.figure( axes, **newFigureProperties )
	if isinstance( axes, plt.Figure ): axes = axes.gca()
	if axes is None and plt.get_fignums() and not mustOpenNewFigure: axes = plt.gca()
	if axes is None: axes = plt.figure( **newFigureProperties ).gca()
	if cla: clear_axes( axes )  #axes.cla()
	if sca: plt.figure( axes.figure.number ); plt.axes( axes )
	return axes

def closefigs( *ff ):
	"""
	A more flexible/lazy version of `plt.close()`, for closing figures.
	
	Supply however many arguments you want. Each argument can be any valid
	`plt.close()` argument: an integer, a `Figure` instance, a figure name,
	or the word 'all'. Additionally, you can supply strings like '2-5',
	'1,3,4,7-9', '-2' and '3-' to specify ranges of figure numbers. Finally,
	any sequence (or iterator) of valid arguments is also a valid argument.
	
	`closefigs()` without any arguments is the same as `closefigs('all')`.
	"""
	if not ff: ff = [ 'all' ]
	plt = load_plt()
	for f in ff:
		if isinstance( f, str ):
			f = [ part.strip() for part in f.split( ',' ) if part.strip() ]
			if len( f ) == 1:
				f = f[ 0 ]
				if f.lower() in [ 'all', '*' ]: f = 'all'
				if not f.startswith( '-' ):
					try: f = int( f )
					except: pass
				if isinstance( f, str ):
					if f.endswith( '+' ): f = f.rstrip( '+' ) + '-'
					try: first, last = [ int( x ) if x.strip() else None for x in f.split( '-' ) ]
					except: pass
					else:
						if first is None: first = min( plt.get_fignums() ) 
						if last is None: last = max( plt.get_fignums() ) 
						f = range( first, last + 1 )
		if callable( getattr( f, '__iter__', None ) ):
			if not f: continue
			if not isinstance( f, str ): closefigs( *f ); continue
		
		#print(repr(f))
		plt.close( f )

apply = lambda x:x()
@apply # so AX will be a singleton instance of this:
class AX( object ):
	"""
	Have you ever experienced this? ::
	
	    LoadDataset().DoThis().DoThat().DoTheOther().Plot(axes=
	    #                                                      ^ ugh...
	    #          I want to ensure I don't overwrite particular plots.
	    #          Or maybe I *do* want to overwrite a particular plot.
	    #        Either way, I now have to switch mental gears, rewind,
	    #          and cue up whichever figure or axes should or should
	    #           not be targeted, *before* I do all of the stuff I'm
	    #         actually trying to think about. But I would prefer my
	    #          thought process to be centered on, and my actions to
	    #         flow from, the data analysis pipeline rather than the
	    #            structure and needs of the matplotlib environment.
	
	The `AX` helper object can target existing figures, create new
	figures, clear figures, create subplot grids if and only if
	they're not already there, target a particular axes, clear
	axes, and control whether or not the targeted figure should become
	the `pyplot` state machine's current figure or the targeted axes
	should become its figure's current axes---all in shorthand and
	without requiring you to backtrack.
	
	Here are some examples (the underscores can be omitted but may
	help readability)::
	
	    axes = AX.f1  # the current axes on figure 1 (create as needed)
	    axes = AX.f12_a0  # the first axes (index 0) on figure 12 (create
	                      # the figure and/or that figure's first axes, as
	                      # needed)
	    axes = AX.s2x3_r0c1  # ensure there is a 2x3 subplot grid on the
	                         # current figure and target the upper middle
	                         # subplot (row 0, column 1)
	    axes = AX.r0c1 # target {row 0, column 1} of the current figure,
	                   # whatever subplot grid it has (this may raise an
	                   # exception if the row or column indices go beyond
	                   # what is there)
	
	Other commands are as follows. Some of them have different effects
	depending on whether they occur before or after "axes selection" - 
	this means before or after the point at which we have started
	to specify any subplot layout or row/column/axes indices.
	
	- `q` before axes selection closes the selected figure (or current
	  figure, if you have not selected one yet). You can then select
	  another one with `f`, create a new one with `n`, or just fall back
	  to whatever `pyplot` now thinks is the current figure.
	
	- `qq` at the beginning closes all figures.
	
	- `n` or `fn`, instead of specifying a figure number, creates a new
	  figure.
	
	- `d` before axes selection allows you to specify the figure
	  dimensions in inches. Results may vary as to whether this
	  successfully modifies the size of an existing figure, but it
	  should work for new figures created implicitly or explicitly.
	  Example:  `d5x4` creates a figure 5 inches wide and 4 inches
	  heigh, and `d5` creates a square 5x5 inch figure.
	  	
	- `b` blanks (i.e. clears) the figure if it occurs before axes
	  selection.  If it occurs after axes selection, it blanks the
	  selected axes.
	
	- `z`, the "sleeper" flag, suppresses state-machine changes. By
	  default, the selected figure will become the `pyplot` state
	  machine's current figure `plt.gcf()`, and the selected axes will
	  become its own figure's current axes, `fig.gca()`. However, you
	  can choose to suppress this: a `z` before axes selection says
	  "target this figure but do not change pyplot's idea of the
	  default figure". Similarly, a `z` after axes selection says
	  "target this axes but do not change the figure's default axes".
	
	- `l` at the end calls `look()` to raise the chosen axes' figure
	  window (results will vary by OS and window-manager, as to whether
	  this succeeds, and whether it also succeeds in focusing the
	  figure so that it receives keyboard input - you may have to click).
	  
	- `h` is similar to `l` but it also calls `hotfig()` to allow
	  keyboard switching between figure windows.
	
	"""
	def __getattr__( self, attrName ):
		import re
		import sys
		previouslyLoaded = ( 'matplotlib.pyplot' in sys.modules )
		import matplotlib, matplotlib.pyplot as plt
		if not previouslyLoaded and 'IPython' in sys.modules: plt.ion()
		class chosen: figure = figWidth = figHeight = nRows = rowIndex = nCols = colIndex = axes = None
		backgroundFigure = backgroundAxes = False		
		
		previousCurrentFigure = plt.gcf() if plt.get_fignums() else None
		windowManagerControls = ''.join( re.findall( r'[hl]+$', attrName.lower() ) )
		attrName = attrName.lower().rstrip( 'hl' ) 
		
		def GetGridDimensions( axes ):
			try: sps = axes.get_subplotspec()
			except: return 1, 1
			return tuple( sps.get_geometry()[ :2 ] )
		def GetSubplotPosition( axes ):
			try: sps = axes.get_subplotspec()
			except: return None, None
			# return sps.rowspan.start, sps.colspan.start   # newest
			# return sps.get_rows_columns()[ 2 ], sps.get_rows_columns()[ 4 ] # older (neither forward nor backward compatible)
			nRows, nCols, flatIndex = sps.get_geometry()[ :3 ] # lowest common denominator
			return int( flatIndex / nCols ), flatIndex % nCols
				
		def NewFigure( n=None ):
			opts = {}
			if chosen.figWidth  is None: chosen.figWidth  = chosen.figHeight
			if chosen.figHeight is None: chosen.figHeight = chosen.figWidth
			if chosen.figHeight is not None: opts[ 'figsize' ] = [ chosen.figWidth, chosen.figHeight ]
			isNew = n in [ None, 'n', 'new' ] or n not in plt.get_fignums()
			figure = plt.figure( n, **opts ) 
			if isNew: pass # TODO: special measures needed to resize pre-existing figure?
			return figure
		def ResolveFigure():
			if chosen.figure is None: chosen.figure = plt.gcf() if plt.get_fignums() else NewFigure()
			if not isinstance( chosen.figure, plt.Figure ): chosen.figure = NewFigure( chosen.figure )
			return chosen.figure
		def ResolveAxes():
			if chosen.axes is None: chosen.axes = ResolveFigure().gca()
			return chosen.axes
		def SelectFigure( char, number ):
			chosen.figure = 'new' if char == 'n' else number
		def EnsureSubplots():
			if chosen.nRows is None: chosen.nRows = 1
			if chosen.nCols is None: chosen.nCols = 1
			figure = ResolveFigure()
			axes = [ ax for ax in figure.axes if GetGridDimensions( ax ) == ( chosen.nRows, chosen.nCols ) ]
			if not axes:
				figure.clf()
				try: figure.subplots( chosen.nRows, chosen.nCols )
				except:
					try: oldgcf = plt.gcf(); plt.figure( figure.number ); [ plt.subplot( chosen.nRows, chosen.nCols, i + 1 ) for i in range( chosen.nRows * chosen.nCols ) ]
					finally: plt.figure( oldgcf.number )
			if chosen.axes is None: chosen.axes = figure.axes[ 0 ]
		def SelectSubplot( row=None, col=None ):
			if row is None: targetRow = 0 if chosen.rowIndex is None else chosen.rowIndex
			else: chosen.rowIndex = targetRow = row 
			if col is None: targetCol = 0 if chosen.colIndex is None else chosen.colIndex
			else: chosen.colIndex = targetCol = col
			axes = [ ax for ax in ResolveFigure().axes if GetSubplotPosition( ax ) == ( targetRow, targetCol ) ]
			if not axes: raise ValueError( 'could not find an axes at row %d column %d of figure %d (remember, row and column indices should be 0-based)' % ( targetRow, targetCol, ResolveFigure().number ) )
			chosen.axes = axes[ 0 ]
		def SelectAxes( n ):
			figure = ResolveFigure()
			axes = figure.axes
			if not axes: axes = [ figure.gca() ]
			try: axes = axes[ n ]
			except: raise ValueError( 'could not find an axes at (zero-based) index %d on figure %d' % ( n, figure.number ) )
			chosen.axes = axes
			
		context = 'figure'
		mode = None
		expectation = { 'q', 'z', 'f', 'n', 'b', 's', 'r', 'c', 'a', 'd' }
		for char in re.findall( r'\d+|\D', attrName ):
			if char == '_': continue
			try: number = int( char )
			except: number = None
			if ( char if number is None else int ) not in expectation: raise ValueError( "unexpected instruction %r" % char )
			if char == 'q' and mode == 'close': mode = None; expectation = { 'f', 'z', 'b', 's', 'r', 'c', 'a', 'd' }; plt.close( 'all' ); continue
			if char == 'q': mode = 'close'; expectation = { 'q', 'f', 'z', 'b', 's', 'r', 'c', 'a', 'd' }; continue
			if mode == 'close':
				mode = None; expectation = { 'f', 'z', 'b', 's', 'r', 'c', 'a', 'd' }
				if plt.get_fignums(): plt.close( ResolveFigure() ); chosen.figure = None
				# and fall through
			if char == 'f': mode = 'figure'; expectation = { 'z', 'n', 'b', int }; continue
			if char == 'z' and context == 'figure': backgroundFigure = True; continue
			if char == 'z' and context == 'axes':   backgroundAxes   = True; continue
			if char == 'b' and context == 'figure': mode = None; expectation = { 's', 'r', 'c', 'a' }; ResolveFigure().clf(); continue
			if char == 'b' and context == 'axes':   mode = None; expectation = { 'z' }; ResolveAxes().cla(); continue
			if char == 'n': mode = 'figure' # and fall through
			if mode == 'figure': mode = None; expectation = { 'q', 'z', 'b', 's', 'r', 'c', 'a', 'd' }; SelectFigure( char, number ); continue
			if char == 'd': mode = 'width'; expectation = { int }; continue
			if mode == 'width': mode = None; expectation = { 'x', 'z', 'b', 's', 'r', 'c', 'a' }; chosen.figWidth = number; continue
			if char == 'x' and context == 'figure': mode = 'height'; expectation = { int }; continue
			if mode == 'height': mode = None; expectation = { 'q', 'z', 'b', 's', 'r', 'c', 'a' }; chosen.figHeight = number; continue
			context = 'axes'
			if char == 's': mode = 'subplots_rows'; expectation = { int }; continue
			if mode == 'subplots_rows': mode = None; expectation = { 'x' }; chosen.nRows = number; continue
			if char == 'x': mode = 'subplots_cols'; expectation = { int }; continue
			if mode == 'subplots_cols': mode = None; expectation = { 'r', 'c', 'a', 'b', 'z' }; chosen.nCols = number; EnsureSubplots(); continue
			if char == 'r': mode = 'select_row'; expectation = { int }; continue
			if mode == 'select_row': mode = None; expectation = { 'r', 'c', 'a', 'b', 'z' }; SelectSubplot( row=number ); continue
			if char == 'c': mode = 'select_col'; expectation = { int }; continue
			if mode == 'select_col': mode = None; expectation = { 'r', 'c', 'a', 'b', 'z' }; SelectSubplot( col=number ); continue
			if char == 'a': mode = 'axes'; expectation = { 'b', 'z', int }; continue
			if mode == 'axes': mode = None; expectation = {}; SelectAxes( number ); continue
			raise RuntimeError( 'internal parsing error at %r' % char )
		
		axes = ResolveAxes()
		if not backgroundAxes: axes.figure.sca( axes )
		if backgroundFigure and previousCurrentFigure is not None: plt.figure( previousCurrentFigure.number )
		else: plt.figure( axes.figure.number )
		if   'h' in windowManagerControls: hotfig(); look( axes.figure )
		elif 'l' in windowManagerControls: look( axes.figure )
		return axes
