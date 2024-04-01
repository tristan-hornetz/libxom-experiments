# libxom-experiments
This repository contains the experiments for my master's thesis "Execute-Only Memory as a Security Hardening Feature on x86-64".
Also see the [libxom repository](https://github.com/tristan-hornetz/libxom).

## Building
You can build all code in this repository with CMake. To install the build dependencies
on a Debian-based distribution, run
```shell
apt install libssl-dev libgcrypt-dev linux-headers-$(uname -r) ocl-icd-opencl-dev
```

### CPU Prerequisites
Some of the experiments require instruction set extensions that are not supported
on some oder or lower-spec CPUs. To run the AES demo, you will need SSE3, AES-NI and PCLMULQDQ.
The HMAC demo additionally requires AVX2, VAES, SHA-NI, and RDRAND.

## Experiments

 * `demos/xom_demo_basic` - A small demo for libxom that serves as a code example.
 * `demos/xom_demo_features` - A demo program that tests all XOM-related features of libxom.
 * `demos/aes-gcm/aes-gcm` - A demo for the AES code
 * `demos/hamc/hmac_sha256` - A demo for the HMAC code
 * `demos/hamc/password_check` - A demo for password checks with XOM for leakage resistance
 * `benchmarks/benchmarks` - Various benchmarks
 * `benchmarks/enc_bench` - Benchmarks for encryption throughput
 * `attacks/interrupts` - PoC code for Interrupt-driven code recovery
 * `attacks/microarchitectre` - PoCs for various microarchitectural attacks against XoM

## Acknowledgements
This repository reuses code from
 * [The Linux Kernel](https://github.com/torvalds/linux.git)
 * [OpenSSL](https://github.com/openssl/openssl.git)
 * [Transient Fail](https://github.com/IAIK/transientfail)

