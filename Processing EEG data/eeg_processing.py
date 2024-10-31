import scipy.io as sio
import mne

#read matlab file and put into data that holds key-value pair
data = sio.loadmat("Subject_A_Test.mat")
eeg_data = data['Signal']

#get signal data for number of trials, time samples, and channels
n_trials, n_time_samples, n_channels = eeg_data.shape
sampling_rate = 512 #sampling rate for BCI Competition III dataset

#create info for MNE object and reshape the EEG data for MNE's format, then create the object
info = mne.create_info(ch_names=[f"ch_{i + 1}" for i in range(n_channels)],
                       sfreq=sampling_rate,
                       ch_types='eeg')
eeg_data_reshaped = eeg_data.transpose(2, 1, 0).reshape(n_channels, -1)
raw = mne.io.RawArray(eeg_data_reshaped, info)

#apply a bandpass filter from 1Hz to 40Hz
raw.filter(1, 40, method='fir')
#plot the eeg data after filtering
raw.plot(duration=10.0, scalings={'eeg': 75e-6})
