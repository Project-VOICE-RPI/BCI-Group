import scipy.io as sio
import mne
import numpy as np
import matplotlib.pyplot as plt


#read matlab file and put into data that holds key-value pair
data = sio.loadmat("Subject_A_Train.mat")

#store eeg signals, flashes of p300 signal and labels
eeg_data = data['Signal']
flashing_data = data['Flashing']
stimulus_code_data = data['StimulusCode'] 
stimulus_type_data = data['StimulusType']

n_trials, n_time_samples, n_channels = eeg_data.shape
sampling_rate = 512
info = mne.create_info(ch_names=[f"ch_{i + 1}" for i in range(n_channels)],
                       sfreq=sampling_rate,
                       ch_types='eeg')

#reshape eeg data for MNE
eeg_data_reshaped = eeg_data.transpose(2, 1, 0).reshape(n_channels, -1)
raw = mne.io.RawArray(eeg_data_reshaped, info)

#apply a bandpass filter from 1Hz to 40Hz
raw.filter(1, 40, method='fir')
events = []

#build the events array with corrected sample indices
for trial_idx in range(flashing_data.shape[0]):
    for time_idx in range(1, flashing_data.shape[1]):
        prev_flash = flashing_data[trial_idx, time_idx - 1]
        flash = flashing_data[trial_idx, time_idx]
        label = stimulus_type_data[trial_idx, time_idx]
        
        #detect rising edge of flash signal
        if prev_flash == 0 and flash == 1:
            event_type = 1 if label == 1 else 2
            sample_idx = time_idx + trial_idx * n_time_samples
            events.append([sample_idx, 0, event_type])

events = np.array(events)

#define dictionary for target/non-target
event_id = {'Target': 1, 'Non-Target': 2}

#create epochs showing a difference between target and non-target events
epochs = mne.Epochs(raw, events, event_id={'Target': 1, 'Non-Target': 2}, 
                    tmin=-0.2, tmax=0.8, baseline=(None, None), preload=True, event_repeated='merge')

#plot the averaged ERPs for target/non-target events
target_evoked = epochs['Target'].average()
nontarget_evoked = epochs['Non-Target'].average()

#compute averaged ERP across all channels for target/non-target events
target_avg_across_channels = target_evoked.data.mean(axis=0)
nontarget_avg_across_channels = nontarget_evoked.data.mean(axis=0)

#plot the averaged ERP across all channels for target events
plt.figure()
plt.plot(target_evoked.times, target_avg_across_channels)
plt.title("Target P300 ERP (Averaged Across Channels)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude (µV)")

#plot the averaged ERP across all channels for non-target events
plt.figure()
plt.plot(nontarget_evoked.times, nontarget_avg_across_channels)
plt.title("Non-Target ERP (Averaged Across Channels)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude (µV)")

plt.show()
