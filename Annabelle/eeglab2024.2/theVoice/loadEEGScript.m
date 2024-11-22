[ALLEEG, EEG, CURRENTSET, ALLCOM] = eeglab;

for i = 1:6 % subject 
    for j = 1:2 % session 
        for k = 1:10 % run
            eegName = sprintf('EEG%d%d_%d', i, j, k);
            eventName = sprintf('Event%d%d_%d', i, j, k);
            dataName = sprintf('Subject_%d%d_r%d', i, j, k);

            EEG = pop_importdata('dataformat','array','nbchan',0,'data', eegName,'srate',512,'pnts',0,'xmin',0);
            [ALLEEG, EEG, CURRENTSET] = pop_newset(ALLEEG, EEG, 0,'setname',dataName,'gui','off'); 

            EEG = pop_importevent( EEG, 'event',eval(eventName),'fields',{'latency','type'},'timeunit',NaN);
            [ALLEEG, EEG, CURRENTSET] = eeg_store(ALLEEG, EEG, CURRENTSET);

            eeglab redraw;
        end

    end
end
