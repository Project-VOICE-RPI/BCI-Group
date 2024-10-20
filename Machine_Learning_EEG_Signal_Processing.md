# A Review on Machine Learning for EEG Signal Processing in Bioengineering

https://pubmed.ncbi.nlm.nih.gov/32011262/
https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8972542

## Summary

## Electroencephalography (EEG)

- Neurons hold a charge which can fluctuate which will be read by an EEG machine.

EEG Waveforms \[inclusive: exclusive]

- Vary based on band, denotes freq range
- Delta band: Slowest wave with highest amplitude. Freq range \[:4]
  - Located frontally in adults, postteriorly in children
- Theta band: Freq range \[4: 8]
  - Most common in young children, signifies drowsiness or arousal in adults.
- Alpha band: Freq range \[8: 14]
  - Correlated to eye muscle movement
  - located on both sides of posterior regions
- Beta band: Freq range \[14:]
  - general motor behavior
  - located on both sides of head's frontal regions

## Machine Learning

EEG Signal Acquisition
-> Preprocessing
-> Feature Extraction
-> Feature Selection
-> ML Training
-> ML Testing

Linear Regression is the most commonly used with EEG data.

### Side Notes

1. Look into EEG scans while gaming, may have good data on how different motor functions map to brain scans.
2. Look into using SVM to classify EEG data.
