from sys import argv
import numpy as np
import matplotlib.pyplot as plt
from numpy import copy
from scipy import signal

#define RUNS_PER_PORT  0x2000
#define NUM_SAMPLES    200

RUNS_PER_PORT  = 0x400
NUM_SAMPLES    = 300
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
    dirname = "."
    if len(argv) > 1:
        dirname = argv[1]

    timings = list()

    for filename in ["p0.bin", "p1.bin", "p5.bin", "p06.bin"]:
        with open(f"{dirname}/{filename}") as f:
            raw = np.array(list(map(lambda i: normalize((int(i) & 0xffffffff) - (int(i) >> 32)), np.fromfile(f, dtype=np.uint64))))

        rounds = raw.reshape(RUNS_PER_PORT, NUM_SAMPLES)
        rounds = np.array(list(np.array(list(reversed(t))) for t in rounds))
        cycle_count = int(min(np.sum(t) for t in rounds) / 10)
        cycle_progress = copy(rounds)
        for i in range(len(cycle_progress)):
            for j in range(1, len(cycle_progress[0])):
                cycle_progress[i][j] += cycle_progress[i][j - 1]
        print(cycle_progress)
        print(cycle_count)

        cycle_latency = np.array(list([0] * cycle_count))
        for i in range(cycle_count):
            cycle_latency[i] = np.sum(list(r[p.searchsorted(i * 10)] for p, r in zip(cycle_progress, rounds)))
        cycle_latency = cycle_latency.astype(np.float64) / len(cycle_progress)
        print(cycle_latency)
        r = 0
        for i in range(1, len(cycle_latency)):
            r = i
            if cycle_latency[i-1] != cycle_latency[i]:
                break
        cycle_latency = np.array(cycle_latency[r:])
        timings.append(cycle_latency)
        #ma4 = running_mean(cycle_latency, 4)
        #ma8 = signal.savgol_filter(cycle_latency, 9, 3)

    f, axarr = plt.subplots(5, sharex=True, sharey=True)
    for i, l in enumerate(timings):
        axarr[i].plot(l)
        axarr[4].plot(l)

    plt.show()


