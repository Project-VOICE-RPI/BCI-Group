[EEGs, Positions, Types, SampleRates, Labels] = Parser('Subject01_s1.mat');

%convert for samples x channels to channels x samples
EEG11_1 = transpose(EEGs{1});
