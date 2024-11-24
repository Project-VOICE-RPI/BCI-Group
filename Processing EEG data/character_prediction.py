import scipy.io as sio
import numpy as np
from scipy.signal import savgol_filter
from joblib import Parallel, delayed
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
import seaborn as sns
from scipy.signal import butter, filtfilt

#calculate variance across time for each channel to select top 20
def select_top_channels(signals, num_channels=20):
    channel_variances = np.var(signals, axis=0)
    top_channel_indices = np.argsort(channel_variances)[-num_channels:]
    
    return signals[:, top_channel_indices]

#batch processing of signal epochs with savitzky-golay filter and baseline correction
def process_signals(epochs, sampling_rate=240, num_channels=20):
    signals = np.mean(epochs[:, :, :num_channels], axis=2)
    
    signals = np.apply_along_axis(lambda x: savgol_filter(x, 11, 3), 1, signals)

    #add bandpass filtering for p300 frequency range
    baselines = np.mean(signals[:, :int(0.4 * sampling_rate)], axis=1)
    nyq = sampling_rate * 0.5
    b, a = butter(3, [0.1/nyq, 20/nyq], btype='band')
    signals = filtfilt(b, a, signals, axis=1)
    
    return signals - baselines[:, None]

#predict a character from a trial by finding valid flashes and extracting epochs for those flashes
def predict_single_character(eeg_chunk, flash_chunk, stim_chunk, stim_type, sampling_rate=240, num_channels=20):
    row_scores = np.zeros(6)
    col_scores = np.zeros(6)
    
    valid_flashes = np.where((flash_chunk == 1) & (stim_type == 1) &
                             (np.arange(len(flash_chunk)) >= 48) & 
                             (np.arange(len(flash_chunk)) < len(flash_chunk) - 192))[0]
    
    
    if len(valid_flashes) == 0:
        return 0, 0 
    
    epochs = np.array([
        eeg_chunk[flash_idx - 48:flash_idx + 192, :num_channels]
        for flash_idx in valid_flashes
    ])
    
    processed_signals = process_signals(epochs, sampling_rate)
    
    #calculate row/column scores from 300-500ms post stimulus
    for i, flash_idx in enumerate(valid_flashes):
        stim = int(stim_chunk[flash_idx])
        if stim < 1 or stim > 12:
            continue

        score = np.mean(processed_signals[i, 74:130])
        
        if stim <= 6:
            col_scores[stim - 1] += score
        else:
            row_scores[stim - 7] += score
    
    return np.argmax(row_scores), np.argmax(col_scores)

def run_p300_speller():
    #load data, extract the arrays from matlab 
    data = sio.loadmat("Subject_B_Train.mat")
    eeg_data = data['Signal']
    flashing = data['Flashing']
    stim_code = data['StimulusCode']
    target_char = data['TargetChar']
    
    #turn the (1x85) string of target characters into a list
    target_char = list(target_char[0])
    num_trials = eeg_data.shape[0]
    
    char_matrix = np.array([
        ['A', 'B', 'C', 'D', 'E', 'F'],
        ['G', 'H', 'I', 'J', 'K', 'L'],
        ['M', 'N', 'O', 'P', 'Q', 'R'],
        ['S', 'T', 'U', 'V', 'W', 'X'],
        ['Y', 'Z', '1', '2', '3', '4'],
        ['5', '6', '7', '8', '9', '_']
    ])
    
    #parallel processing for all trials
    def process_trial(trial_idx):
        eeg_chunk = eeg_data[trial_idx]
        flash_chunk = flashing[trial_idx]
        stim_chunk = stim_code[trial_idx]
        actual = target_char[trial_idx]
        stim_type = data['StimulusType'][trial_idx]
        
        row, col = predict_single_character(eeg_chunk, flash_chunk, stim_chunk, stim_type)
        pred_char = char_matrix[row, col]
        return actual, pred_char
    
    results = Parallel(n_jobs=-1)(delayed(process_trial)(i) for i in range(num_trials))
    
    #unpack results and find accuracy
    actual_chars, predictions = zip(*results)
    correct = sum(1 for p, a in zip(predictions, actual_chars) if p == a)
    accuracy = (correct / num_trials) * 100
    
    return predictions, actual_chars, accuracy

predictions, actuals, accuracy = run_p300_speller()

#display first 10 trials results
print(f"\nP300 Speller Results:")
print(f"Overall Accuracy: {accuracy:.2f}%")
print(f"Total Predictions: {len(predictions)}")
print("\nCharacter Predictions (First 10):")
print("-" * 50)
print("Trial | Predicted | Actual | Correct")
print("-" * 50)

for i, (pred, actual) in enumerate(zip(predictions, actuals)):
    if i >= 10:
        break
    correct = "✓" if pred == actual else "✗"
    print(f"{i+1:5d} | {pred:9s} | {actual:6s} | {correct:7s}")
    
#create confusion matrix
unique_chars = list(set(actuals))
cm = confusion_matrix(actuals, predictions, labels=unique_chars)

plt.figure(figsize=(10, 8))
sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", xticklabels=unique_chars, yticklabels=unique_chars)
plt.xlabel("Predicted Characters")
plt.ylabel("Actual Characters")
plt.title("Confusion Matrix of Predictions")
plt.show()
plt.ylabel("Actual Characters")
plt.title("Confusion Matrix of Predictions")
plt.show()
