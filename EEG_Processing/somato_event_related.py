"""
Goal: Figure out how to use events in mne
Author: Dante Luis
Sources: https://mne.tools/stable/auto_examples/time_frequency/time_frequency_global_field_power.html#ex-time-freq-global-field-power
"""

import matplotlib.pyplot as plt
import mne
import numpy as np
from mne.baseline import rescale
from mne.datasets import somato
from mne.stats import bootstrap_confidence_interval

data_path = somato.data_path()
subject = "01"
task = "somato"
raw_fname = data_path / f"sub-{subject}" / "meg" / f"sub-{subject}_task-{task}_meg.fif"

iter_freqs = [("Theta", 4, 7), ("Alpha", 8, 12), ("Beta", 13, 25), ("Gamma", 30, 45)]

event_id, tmin, tmax = 1, -1.0, 3.0
baseline = None

raw = mne.io.read_raw_fif(raw_fname)
events = mne.find_events(raw, stim_channel="STI 014")

frequency_map = list()

for band, fmin, fmax in iter_freqs:
    raw = mne.io.read_raw_fif(raw_fname)
    raw.pick(picks=["grad", "eog"])
    raw.load_data()

    raw.filter(
        fmin,
        fmax,
        n_jobs=None,
        l_trans_bandwidth=1,
        h_trans_bandwidth=1,
    )

    epochs = mne.Epochs(
        raw,
        events,
        event_id,
        tmin,
        tmax,
        baseline=baseline,
        reject=dict(grad=4000e-13, eog=350e-6),
        preload=True,
    )

    epochs.subtract_evoked()

    epochs.apply_hilbert(envelope=True)
    frequency_map.append(((band, fmin, fmax), epochs.average()))
    del epochs
del raw


# Helper function for plotting spread
def stat_fun(x):
    """Return sum of squares."""
    return np.sum(x**2, axis=0)


# Plot
fig, axes = plt.subplots(4, 1, figsize=(10, 7), sharex=True, sharey=True)
colors = plt.colormaps["winter_r"](np.linspace(0, 1, 4))
for ((freq_name, fmin, fmax), average), color, ax in zip(
    frequency_map, colors, axes.ravel()[::-1]
):
    times = average.times * 1e3
    gfp = np.sum(average.data**2, axis=0)
    gfp = mne.baseline.rescale(gfp, times, baseline=(None, 0))
    ax.plot(times, gfp, label=freq_name, color=color, linewidth=2.5)
    ax.axhline(0, linestyle="--", color="grey", linewidth=2)
    ci_low, ci_up = bootstrap_confidence_interval(
        average.data, random_state=0, stat_fun=stat_fun
    )
    ci_low = rescale(ci_low, average.times, baseline=(None, 0))
    ci_up = rescale(ci_up, average.times, baseline=(None, 0))
    ax.fill_between(times, gfp + ci_up, gfp - ci_low, color=color, alpha=0.3)
    ax.grid(True)
    ax.set_ylabel("GFP")
    ax.annotate(
        f"{freq_name} ({fmin:d}-{fmax:d}Hz)",
        xy=(0.95, 0.8),
        horizontalalignment="right",
        xycoords="axes fraction",
    )
    ax.set_xlim(-1000, 3000)

axes.ravel()[-1].set_xlabel("Time [ms]")

plt.show()
input("Press Enter to end...")
