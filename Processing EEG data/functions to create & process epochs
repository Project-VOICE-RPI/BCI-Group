import scipy.io as sio
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter

def create_epochs(eeg_data, flashing_data, stimulus_type_data, voltage_threshold=200,noise_level=1.5):
    epoch_data = []
    epoch_labels = []
    
    pre_samples = int(0.2 * sampling_rate)
    post_samples = int(0.8 * sampling_rate)
    
    for trial_idx in range(eeg_data.shape[0]):
        flash_onsets = np.where(np.diff(flashing_data[trial_idx]) > 0)[0] + 1
        
        for onset in flash_onsets:
            if onset < pre_samples or onset + post_samples > eeg_data.shape[1]:
                continue
                
            #extract epoch
            epoch = eeg_data[trial_idx, onset - pre_samples:onset + post_samples, :]
            
            noise = np.random.normal(0, noise_level, epoch.shape)
            epoch = epoch + noise
            
            #look for artifacts
            if np.any(np.abs(epoch) > voltage_threshold):
                continue
                
            label = stimulus_type_data[trial_idx, onset]
            epoch_data.append(epoch)
            epoch_labels.append(label)
            
    return np.array(epoch_data), np.array(epoch_labels)

def process_epoch(epoch):
    #spatial filter (weighted average across channels)
    weights = np.ones(epoch.shape[1]) * 0.5
    central_channels = slice(epoch.shape[1]//3, 2*epoch.shape[1]//3)
    weights[central_channels] = 0.1
    
    spatial_filtered = np.average(epoch, axis=1, weights=weights)
    car_filtered = spatial_filtered - (np.mean(spatial_filtered) * 0.5)
    
    window_length = min(11,21)
    smoothed = savgol_filter(car_filtered, window_length=window_length, polyorder=2)
    
    #baseline correction
    baseline_period = smoothed[:int(0.2 * sampling_rate)]
    baseline_mean = np.mean(baseline_period) * 0.7
    baseline_std = np.std(baseline_period) + 1e-6
    
    return (smoothed - baseline_mean) / baseline_std
