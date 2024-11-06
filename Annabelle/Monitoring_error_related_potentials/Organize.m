% Makes inputs and outputs datapoints

for i=1:6
    for j=1:2
        File = ['Subject0', num2str(i), '_s', num2str(j), '.mat'];
        EEGs, Positions, Types = Parser(File);
    end
end