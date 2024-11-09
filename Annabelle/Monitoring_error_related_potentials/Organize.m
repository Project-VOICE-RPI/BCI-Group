function x = getFeature(Sample)
    x = [1 1 1];
end

% Makes inputs and outputs datapoints
X = [];
Y = [];
for i=1:6
    for j=1:2
        File = ['Subject0', num2str(i), '_s', num2str(j), '.mat'];
        [EEGs, Positions, Types, SampleRates, Labels] = Parser(File);
        
        for k=1:10
            eeg = EEGs{1};
            label = Labels{1};

            pos = Positions{1};
            type = Types{1};
            %GETTING VALID SAMPLES FEATURES AND CLASSIFICATION
            for l=i:size(pos, 1)
                if type(l) == 5 || type(l) == 10
                    X = [X; getFeature( eeg(pos(l), :) )];
                    Y = [Y; 1];
                elseif type(l) == 6 || type(l) == 9
                    X = [X; getFeature( eeg(pos(l), :) )];
                    Y = [Y; -1];
                end
            end
        
        end
        
    end
end


%File = 'Subject01_s1.mat';
%[EEGs, Positions, Types, SampleRates, Labels] = Parser(File);