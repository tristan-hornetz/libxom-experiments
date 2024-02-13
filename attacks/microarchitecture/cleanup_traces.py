from sys import argv
import numpy as np
import matplotlib.pyplot as plt

CEIL = 512


def normalize(x):
    if x > CEIL:
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

    ma4 = running_mean(raw, 4)

    print(ma4)
    f, axarr = plt.subplots(2, sharex=True, sharey=True)
    axarr[0].plot(raw)
    axarr[1].plot(ma4)
    plt.show()


