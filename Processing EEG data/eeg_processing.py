import scipy.io as sio
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter

#read matlab file and put into data that holds key-value pair
data = sio.loadmat("Subject_A_Train.mat")

#store eeg signals, flashes of p300 signal and labels
eeg_data = data['Signal']
flashing_data = data['Flashing']
stimulus_type_data = data['StimulusType']
sampling_rate = 240 #can be reduced to decrease computation time

#create and process epochs
epochs, labels = create_epochs(eeg_data, flashing_data, stimulus_type_data)
target_epochs = epochs[labels == 1]
nontarget_epochs = epochs[labels == 0]

target_processed = np.array([process_epoch(epoch) for epoch in target_epochs])
nontarget_processed = np.array([process_epoch(epoch) for epoch in nontarget_epochs])

#find averages and create time axis
target_avg = np.mean(target_processed, axis=0)
nontarget_avg = np.mean(nontarget_processed, axis=0)
difference_wave = target_avg - nontarget_avg
times = np.linspace(-200, 800, target_avg.shape[0])

#plot target/non-target ERP
plt.figure(figsize=(12, 8))
plt.plot(times, target_avg, 'b-', label='Target', linewidth=2)
plt.plot(times, nontarget_avg, 'r--', label='Non-Target', linewidth=2)
plt.axvline(x=300, color='gray', linestyle=':', alpha=0.5)
plt.axhline(y=0, color='black', linestyle='-', alpha=0.1)
plt.axvspan(300, 500, color='yellow', alpha=0.1)
plt.xlabel('Time (ms)')
plt.ylabel('Amplitude (z-score)')
plt.title('P300 ERP Comparison')
plt.grid(True, alpha=0.3)
plt.legend()

#find and annotate P300 peak (300-500ms)
p300_window = np.logical_and(times >= 300, times <= 500)
p300_peak_idx = np.argmax(difference_wave[p300_window]) + np.where(p300_window)[0][0]
p300_peak_time = times[p300_peak_idx]
print(f"P300 Peak Latency: {p300_peak_time:.1f}ms")

plt.show()


p300_start = int(300 / 1000 * sampling_rate)
p300_end = int(500 / 1000 * sampling_rate)

#calculate signal power of target signal
target_signal_power = np.mean(target_avg[p300_start:p300_end] ** 2)

#calculate noise power of non-target signal
nontarget_noise_power = np.mean(nontarget_avg[p300_start:p300_end] ** 2)

snr_db = 10 * np.log10(target_signal_power / nontarget_noise_power)
print(f"Signal-to-Noise Ratio (SNR): {snr_db:.2f} dB")