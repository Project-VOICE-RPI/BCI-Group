function [EEGs, Positions, Types] = Parser(File)
    %  Returns a list containing the an array of raw eeg data, 
    %       an array of event positions, and an array of event types
    %  File:  file to read
    
    run = importfile(File);

    EEGs = {};
    Positions = {};
    Types = {};
    
    for i=1:10
        STRUCT = run(i);
        RUN = STRUCT{1};
        EEG_DATA = RUN.eeg;
        HEADER = RUN.header;
        EVENT = HEADER.EVENT;
        Position = EVENT.POS;
        Type = EVENT.TYP;
    
        EEGs{end+1} = EEG_DATA;
        Positions{end+1} = Position;
        Types{end+1} = Type;
    end
end

function run = importfile(fileToRead)
    %  Imports data from the specified file
    %  FILETOREAD:  file to read
    
    % Import the file
    newData = load('-mat', fileToRead);
    
    vars = fieldnames(newData);
    run = newData.(vars{1});
end

%TESTING
%File = 'Subject01_s1.mat';
%[EEGs, Positions, Types] = Parser(File);