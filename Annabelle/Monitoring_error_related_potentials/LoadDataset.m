% Makes Variables EEGij_k with i = subject number, j = session number, and
% k = run number and assigns the raw eeg data in EEGLAB format

for i = 1:1 % subject 
    for j = 1:2 % session 
        File = ['Subject0', num2str(i), '_s', num2str(j), '.mat'];
        [EEGs, Positions, Types, ~, Labels] = Parser(File);

        for k = 1:10 % run
            eegName = sprintf('EEG%d%d_%d', i, j, k);
            eventName = sprintf('Event%d%d_%d', i, j, k);
            
            %convert for samples x channels to channels x samples
            eeg = transpose(EEGs{k});
            event = eventArray(Positions{k}, Types{k});

            eval([eegName ' = eeg;']);
            eval([eventName ' = event;']);
        end

    end
end

function event = eventArray(Positions, Types)
    m = size(Positions, 1);
    event = [Positions Types];
end