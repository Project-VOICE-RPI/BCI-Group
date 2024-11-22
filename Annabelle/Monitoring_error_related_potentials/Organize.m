% Makes inputs and outputs datapoints
X = [];
Y = [];

yesx1 = [];
yesx2 = [];
nox1 = [];
nox2 = [];
for i=1:6
    for j=1:2
        File = ['Subject0', num2str(i), '_s', num2str(j), '.mat'];
        [EEGs, Positions, Types, SampleRates, Labels] = Parser(File);
        
        for k=1:10
            eeg = EEGs{k};
            label = Labels{k};

            pos = Positions{k};
            type = Types{k};

            %GETTING VALID SAMPLES FEATURES AND CLASSIFICATION
            for l=i:size(pos, 1)
                if type(l) == 5 || type(l) == 10
                    x = getFeature( eeg(pos(l), :), label );
                    X = [X; x];
                    Y = [Y; 1];

                    yesx1 = [yesx1; x(1, 2)];
                    yesx2 = [yesx2; x(1, 3)];
                elseif type(l) == 6 || type(l) == 9
                    x = getFeature( eeg(pos(l), :), label );
                    X = [X; x];
                    Y = [Y; -1];

                    nox1 = [nox1; x(1, 2)];
                    nox2 = [nox2; x(1, 3)];
                end
            end
        
        end
        
    end
end

function x = getFeature(Sample, Labels)
    frontal = 0;
    countf = 0;
    occipital = 0;
    counto = 0;

    frontals = 'Fpz Fp1 Fp2 AF7 AF3 AFz AF4 AF8 F3 F1 Fz F2 F4';
    occipitals = 'O1 Oz O2 Iz';
    for i=1:size(Labels, 1)
        if contains(frontals, Labels(i, 1))
            frontal = frontal + Sample(1, i);
            countf = countf + 1;
        elseif contains(occipitals, Labels(i, 1))
            occipital = occipital + Sample(1, i);
            counto = counto + 1;
        end
    end
    
    frontal = frontal/countf;
    occipital = occipital/counto;
    x = [1 frontal occipital];
end

hold on;
scatter(yesx1, yesx2);
scatter(nox1, nox2);
legend('yes', 'no');
hold off;