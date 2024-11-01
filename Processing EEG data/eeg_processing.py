import scipy.io as sio
import mne
import numpy as np

#read matlab file and put into data that holds key-value pair
data = sio.loadmat("Subject_A_Test.mat")

#store eeg signals, flashes of p300 signal and labels
eeg_data = data['Signal']
events_data = data['Flashing']
labels = data['StimulusCode'] 

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
events = np.array([
    [int(t * sampling_rate), 0, 1 if label == 1 else 2]
    for t, flash, label in zip(events_data[:, 0], events_data[:, 0], labels[:, 0])
])

#define dictionary for target/non-target
event_id = {'Target': 1, 'Non-Target': 2}

#create epochs showing a difference between target and non-target events
epochs = mne.Epochs(raw, events, event_id=event_id, tmin=-0.2, tmax=0.8,
                    baseline=(None, 0), preload=True, event_repeated='merge')

#plot the averaged ERPs for target and non-target events
target_evoked = epochs['Target'].average()
nontarget_evoked = epochs['Non-Target'].average()

#plot ERP for target and non-target evntsr
target_fig = target_evoked.plot()
target_fig.suptitle("Target P300 ERP")

nontarget_fig = nontarget_evoked.plot()
nontarget_fig.suptitle("Non-Target ERP")
