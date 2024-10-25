import mne
import numpy as np

# Preparing the data
somato = mne.datasets.somato.data_path()
subject = "sub-01"
task = "task-somato"

raw_fname = somato / subject / "meg" / f"{subject}_{task}_meg.fif"
raw_data = mne.io.read_raw_fif(raw_fname)
raw_data.crop(120, 360).load_data().resample(200)

events = mne.find_events(raw_data, stim_channel="STI 014")

picks = mne.pick_types(raw_data.info, meg="grad", eeg=False, eog=True, stim=False)

event_id, tmin, tmax = 1, -1.0, 3.0
baseline = (None, 0)

epochs = mne.Epochs(
    raw_data,
    events,
    event_id,
    tmin,
    tmax,
    picks=picks,
    baseline=baseline,
    reject=dict(grad=4000e-13, eog=350e-6),
    preload=True,
)
