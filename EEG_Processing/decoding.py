import matplotlib.pyplot as plt
import mne
import numpy as np
from mne.datasets import sample
from mne.decoding import (CSP, GeneralizingEstimator, LinearModel, Scaler,
                          SlidingEstimator, Vectorizer, cross_val_multiscore,
                          get_coef)
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler

data_path = sample.data_path()

subjects_dir = data_path / "subjects"
meg_path = data_path / "MEG" / "sample"
raw_fname = meg_path / "sample_audvis_filt-0-40_raw.fif"
tmin, tmax = -0.200, 0.500
event_id = {"Auditory/Left": 1, "Visual/Left": 3}
raw = mne.io.read_raw_fif(raw_fname)
raw.pick(picks=["grad", "stim", "eog"])

raw.load_data().filter(2, 20)
events = mne.find_events(raw, "STI 014")

raw.info["bads"] += ["MEG 2443"]

epochs = mne.Epochs(
    raw,
    events,
    event_id,
    tmin,
    tmax,
    proj=True,
    picks=("grad", "eog"),
    baseline=(None, 0.0),
    preload=True,
    reject=dict(grad=4000e-13, eog=150e-6),
    decim=3,
    verbose="error",
)
epochs.pick(picks="meg", exclude="bads")
del raw

x = epochs.get_data(copy=False)
y = epochs.events[:, 2]
