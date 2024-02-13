from sys import argv
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

RUNS_PER_PORT  = 0x100
NUM_SAMPLES    = 0x2000
CEIL = 512


def normalize(x):
    if x > CEIL:
        x = CEIL
    if x < 0:
        x = CEIL
    return x


def running_mean(x, N):
    cumsum = np.cumsum(np.insert(x, 0, 0))
    return (cumsum[N:] - cumsum[:-N]) / N


if __name__ == "__main__":
    filename = "./p0.bin"
    if len(argv) > 1:
        filename = argv[1]

    with open(filename) as f:
        raw = np.array(list(map(lambda i: normalize((int(i) & 0xffffffff) - (int(i) >> 32)), np.fromfile(f, dtype=np.uint64))))

    rounds = raw.reshape(RUNS_PER_PORT, NUM_SAMPLES)
    cycle_count = int(min(np.sum(t) for t in rounds) / 100)
    cycle_progress = np.array(list(np.array(list(reversed(t))) for t in rounds))
    for i in range(len(cycle_progress)):
        for j in range(1, len(cycle_progress[0])):
            cycle_progress[i][j] += cycle_progress[i][j - 1]
    print(cycle_progress)
    print(cycle_count)

    cycle_latency = np.array(list([0] * cycle_count))
    for i in range(cycle_count):
        for p, r in zip(cycle_progress, rounds):
            j = p.searchsorted(i * 100)
            cycle_latency[i] += r[j]
        if i % 10000 == 0:
            print(i)
    cycle_latency = cycle_latency.astype(np.float64) / len(cycle_progress)
    print(cycle_latency)

    ma4 = running_mean(cycle_latency, 4)
    ma8 = signal.savgol_filter(cycle_latency, 9, 3)

    print(ma4)
    f, axarr = plt.subplots(3, sharex=True, sharey=True)
    axarr[0].plot(cycle_latency)
    axarr[1].plot(ma4)
    axarr[2].plot(ma8)
    plt.show()


