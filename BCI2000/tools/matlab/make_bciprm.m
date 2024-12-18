function [pstr, p] = make_bciprm(varargin)
% MAKE_BCIPRM   Collate BCI2000 parameters from various different sources
% 
% [PSTR, P] = MAKE_BCIPRM(....)
%
% Collates BCI2000 parameters from one or more sources, outputting the
% result as text.  Arguments are taken in order from left to right, with
% later parameter entries overwriting earlier ones if their names match.
% 
% Arguments may be anything supported by READ_BCIPRM:
% 
% (A) Names of, or paths to, BCI2000 .dat files.  The mex-file LOAD_BCIDAT
%     is used to read the parameters from the file (if this has been
%     compiled from the same C++ source revision as the CONVERT_BCIPRM
%     mex-file, then it should return exactly the same struct format as the 
%     options below, which use CONVERT_BCIPRM).
% 
% (B) Names of, or paths to, BCI2000 .prm files.
% 
% (C) One-line strings containing the text content of a BCI2000 .prm file
%     (including newline characters). 
% 
% (D) Cell arrays in which each cell is a parameter string (one of the
%     formats output by CONVERT_BCIPRM) 
% 
% (E) Already-parsed structures (the other format output by CONVERT_BCIPRM)
% 
% (F) Structures, such as those output by BCI2000CHAIN, that contain
%     format (E) in a subfield called .Parms
% 
% Parameters may also be overwritten singly on the command-line:
% 
%     PSTR = MAKE_BCIPRM( someDataFile, someParameterFile, ...
%             'WindowLength', '0.3s',  'ModelOrder', 25,  'OutputType', S ) 
% 
%     In this example, WindowLength and ModelOrder must already be present
%     in the preceding inputs, because only the value is supplied here: the
%     meta-info, such as parameter type, is missing. OutputType (in this
%     example) is exempt from this requirement if S is a suitable parameter
%     substructure, e.g. from  P = READ_BCIPRM(DATFILE);  S = P.OutputType;
% 
% At any point in the sequence, the collated output so far may be written
% to a .prm file using the special argument '>' (or you can use '>>' to
% append rather than overwrite).  For example: 
% 
%     MAKE_BCIPRM(......,    '>',  'collated.prm',    .....)
% 
% The final outputs of the function are:
%     PSTR:   collated parameters as text (format C)
%        P:   collated parameters as a struct (format E)
% 
% MAKE_BCIPRM has the following dependencies:
% 
% M-files:   read_bciprm
% Mex-files: load_bcidat, convert_bciprm

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% $Id: make_bciprm.m 7195 2023-02-07 18:31:03Z mellinger $ 
%% Author: Jeremy Hill <jezhill@gmail.com>
%%
%% $BEGIN_BCI2000_LICENSE$
%% 
%% This file is part of BCI2000, a platform for real-time bio-signal research.
%% [ Copyright (C) 2000-2023: BCI2000 team and many external contributors ]
%% 
%% BCI2000 is free software: you can redistribute it and/or modify it under the
%% terms of the GNU General Public License as published by the Free Software
%% Foundation, either version 3 of the License, or (at your option) any later
%% version.
%% 
%% BCI2000 is distributed in the hope that it will be useful, but
%%                         WITHOUT ANY WARRANTY
%% - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
%% A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
%% 
%% You should have received a copy of the GNU General Public License along with
%% this program.  If not, see <http://www.gnu.org/licenses/>.
%% 
%% $END_BCI2000_LICENSE$
%% http://www.bci2000.org 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


pretty = 0;
p = struct;

while ~isempty(varargin)
	arg = varargin{1};
	varargin(1) = [];
	if ischar(arg)
		if isequal(arg, '-p')
			pretty = 1;
			continue
		end
		if isequal(arg, '-u')
			pretty = 0;
			continue
		end
		if isequal(arg, '>>')
			if isempty(varargin), error('argument ''>>'' was supplied without any subsequent filename'), end
			file = varargin{1}; varargin(1) = [];
			writefile(file, 'at', struct2string(p, pretty));
			continue
		end
		if strncmp(arg, '>>', 2)
			file = deblank(fliplr(deblank(fliplr(arg(3:end)))));
			writefile(file, 'at', struct2string(p, pretty));
			continue
		end
		if isequal(arg, '>')
			if isempty(varargin), error('argument ''>'' was supplied without any subsequent filename'), end
			file = varargin{1}; varargin(1) = [];
			writefile(file, 'wt', struct2string(p, pretty));
			continue
		end
		if strncmp(arg, '>', 1)
			file = deblank(fliplr(deblank(fliplr(arg(2:end)))));
			writefile(file, 'wt', struct2string(p, pretty));
			continue
		end
		if all(ismember(arg, ['a':'z' 'A':'Z' '0':'9' '/']))
			if isempty(varargin), error('parameter keyword ''%s'' was supplied without any subsequent value', arg), end
			paramPath = arg; val = varargin{1}; varargin(1) = [];

            % first, add or set the parameter with its exact path
            if isstruct(val)
                s = val;
            else
                s = get_param(p, paramPath);
            end
            if isempty(s) % parameter does not exist
                s = struct;
                s.Type = 'variant';
                s.Value = val2cellstr(val);
                s.LowRange = '';
                s.HighRange = '';
                s.DefaultValue = '';
                s.Comment = '';
                s.Section = '';
            else % parameter exists
                if isfield(s, 'NumericValue'), s = rmfield(s, 'NumericValue'); end
                s.Value = val2cellstr(val);
                if strncmp(fliplr(s.Type), fliplr('list'), 4), s.Value = s.Value(:); end
                % TODO: perhaps give a warning if the old value had a unit but the new unit did not (for simplicity, only do this if scalar....)
            end
            p = set_param(p, paramPath, s);
			continue
		end
		% for all other kinds of strings, fall through and assume read_bciprm can deal with it
	end
	
	arg = read_bciprm(arg); % to struct from whatever (struct already,  dat filename,  prm filename,  or prm content as newline-delimited string or cell array of strings)
	
	paths = list_param_paths(arg);
    for i = 1:numel(paths)
		paramPath = paths{i};
		paramDetails = get_param(arg, paramPath);
        existingPaths = match_param_paths(p, paramPath);
        if isempty(existingPaths)
            p = set_param(p, paramPath, paramDetails);
        else
            for j = 1:numel(existingPaths)
                s = get_param(p, existingPaths{j}); % if it already exists, preserve the meta-info from previous occurrences, and update the Value
                if isfield(s, 'NumericValue'), s = rmfield(s, 'NumericValue'); end
                s.Value = paramDetails.Value;
                if isfield(paramDetails, 'RowLabels'), s.RowLabels = paramDetails.RowLabels; end
                if isfield(paramDetails, 'ColumnLabels'), s.ColumnLabels = paramDetails.ColumnLabels; end
                p = set_param(p, existingPaths{j}, s);
            end
        end
    end	
end
pstr = struct2string(p, pretty);
if nargout >= 2
	p = convert_bciprm(convert_bciprm(p)); % refresh any NumericValue fields that have changed
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function writefile(filename, mode, content)

if isempty(filename), error('empty output filename'), end
fid = fopen(filename, mode);
if fid == -1, error(['could not open file ''' filename ''' in mode ''' mode(1) '''']), end
fprintf(fid, '%c', content);
if fclose(fid) ~= 0, warning(['unable to close file ''' filename '''']), end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function pstr = struct2string(p, pretty);

if nargin < 2, pretty = []; end
if isempty(pretty), pretty = 1; end

if pretty
	paths = get_paths(p);
	for i = 1:numel(paths)
		s = match_param(p, paths{i});
		s.LowRange = '';
		s.HighRange = '';
		s.DefaultValue = '';
		put_param(p, paths{i}, s);
	end
end

pstr = convert_bciprm(p); % from struct to cell array of strings

if pretty, pstr = make_pretty(pstr); end

pstr = pstr(:)';
pstr(2, :) = {char([13 10])};
pstr = [pstr{:}];
pstr = strrep(pstr, [char(13) char(10)], char(10));
pstr = strrep(pstr, [char(13)], char(10));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function val = val2cellstr(val)

if isnumeric(val), val = num2cell(val); end
if ~iscell(val), val = {val}; end
for i = 1:numel(val)
	if iscell(val{i})
		val{i} = val2cellstr(val{i});
	elseif isnumeric(val{i})
		val{i} = num2str(val{i});
	end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function s = make_pretty(s)
if numel(s) == 0, return, end
for i = 1:numel(s)
	keepgoing = 1;
	p = strrep(s{i}, ' % % % //', ' //');
	[tabs{i,1} p] = strtok(p, ' ');
	[types{i,1} p] = strtok(p, ' ');
	[keys{i,1} p] = strtok(p, ' ');
	rows{i,1} = ''; cols{i, 1} = ''; firstvals{i,1} = '';
	if strncmp(fliplr(types{i}), fliplr('list'), 4)
		[cols{i,1} p] = strtok(p, ' ');
	elseif strncmp(fliplr(types{i}), fliplr('matrix'), 6)
		[tok suffix] = strtok(p, ' ');
		if strncmp(tok, '{', 1)
			keepgoing = 0;
		else
			[rows{i,1}, p] = deal(tok, suffix);
			[tok suffix] = strtok(p, ' ');
			if strncmp(tok, '{', 1)
				keepgoing = 0;
			else
				[cols{i,1}, p] = deal(tok, suffix);
			end
		end
	end
	if keepgoing
		[tok suffix] = strtok(p, ' ');		
		nn = min(find(~ismember([tok '.'], '0123456789-'))) - 1;
		isscalar = strncmp(strtok(suffix, ' '), '//', 2);
		if nn == 0 & isscalar
			ns = max(0, 5-numel(tok));
		else
			ns = max(0, 5 - nn);
		end
		tok = [repmat(' ', 1, ns) tok];
		if isscalar & numel(tok) < 12, suffix = [repmat(' ', 1, 12-numel(tok)) suffix]; end
		if numel(tok) < 12 & ~strncmp(tok, '//', 2)
			[firstvals{i} p] = deal(tok, suffix);
		end
	end
	rest{i,1} = p;
end
spc = repmat(' ', numel(s), 1);
left = num2cell([char(tabs) spc spc char(types) spc spc char(keys) spc], 2);
middle = num2cell([char(strjust(char(rows), 'right')) spc char(strjust(char(cols), 'right')) spc spc spc char(firstvals) spc], 2);
right = rest;
for i = 1:numel(s)
	if ~strncmp(rest{i}, ' //', 3), middle{i} = [deblank(middle{i})]; end
	s{i} = [left{i} middle{i} rest{i}];
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function s = get_param(p, paramPath)
  s = [];
  elements = split_param_path(paramPath);
  for i = 1:numel(elements)
    if ~isfield(p, elements{i})
      return;
    end
    p = p.(elements{i});
  end
  if isfield(p, 'Value')
    s = p;
  end
  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function s = match_param_paths(p, paramPath)
  s = {};
  p1 = split_param_path(paramPath);
  p1 = flip(p1);
  paths = list_param_paths(p);
  for i = 1:numel(paths)
      p2 = split_param_path(paths{i});
      p2 = flip(p2);
      if (numel(p1) > numel(p2))
           continue;
      end
      j = 1;
      while j <= numel(p1) && strcmp(p1{j}, p2{j})
          j = j + 1;
      end
      if j > numel(p1)
          s{numel(s)+1} = paths{i}; %#ok<AGROW>
      end
  end
  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function p = set_param(p, paramPath, s)
  elements = split_param_path(paramPath);
  p = setfield(p, elements{:}, s);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function list = list_param_paths(p)
  list = {};
  fn = fieldnames(p);
  for i = 1:numel(fn)
    if isfield(p.(fn{i}), 'Value')
      list{numel(list)+1} = fn{i}; %#ok<AGROW>
     else
       list2 = list_param_paths(p.(fn{i}));
       list2 = prepend_all_items_with(list2, [fn{i} '/']);
       list = append(list, list2);
     end
  end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function elements = split_param_path(paramPath)
  elements = split(paramPath, '/');
  elements = cellstr(elements);
  if isempty(elements{1})
      elements(1) = [];
  end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function list = prepend_all_items_with(list, s)
  for i = 1:numel(list)
    list{i} = [s list{i}];
  end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function list3 = append(list1, list2)
  list3 = list1;
  for i = 1:numel(list2)
    list3{numel(list3)+1} = list2{i};
  end
