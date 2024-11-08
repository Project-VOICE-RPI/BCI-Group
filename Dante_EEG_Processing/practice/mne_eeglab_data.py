import numpy as np
import mne

mne.io.read_raw_eeglab('./eeglab_data-ucsd.set').plot()
input()
