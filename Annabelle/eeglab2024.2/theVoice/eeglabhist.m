% EEGLAB history file generated on the 22-Nov-2024
% ------------------------------------------------

EEG.etc.eeglabvers = '2024.2'; % this tracks which version of EEGLAB is being used, you may ignore it
EEG.setname='Subject_11_r1';
EEG = pop_eegfiltnew(EEG, 'hicutoff',60,'revfilt',1,'plotfreqz',1);
pop_eegplot( EEG, 1, 1, 1);
