% Makes Variables EEGij_k with i = subject number, j = session number, and
% k = run number and assigns the raw eeg data in EEGLAB format

for i = 1:6 % subject 
    for j = 1:2 % session 
        File = ['Subject0', num2str(i), '_s', num2str(j), '.mat'];
        [EEGs, ~, ~, ~, ~] = Parser(File);

        for k = 1:10 % run
            varName = sprintf('EEG%d%d_%d', i, j, k);
            
            %convert for samples x channels to channels x samples
            eeg = transpose(EEGs{k});

            eval([varName ' = eeg;']);
        end

    end
end