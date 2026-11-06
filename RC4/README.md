# RC4 Encryption Algorithm and Performance Benchmarking in C

A C implementation of the RC4 (Rivest Cipher 4) stream cipher with hardware performance profiling using the x86/x64 timestamp counter (`__rdtsc()`).

This project implements the Key Scheduling Algorithm (KSA) and Pseudo-Random Generation Algorithm (PRGA) separately to measure their computational performance.

## Overview

This implementation demonstrates:

- RC4 state initialization.
- Key Scheduling Algorithm (KSA).
- Pseudo-Random Generation Algorithm (PRGA).
- Generation of pseudorandom keystream bytes.
- XOR-based encryption and decryption.
- Hardware performance measurement using `__rdtsc()`.
- Average KSA CPU cycles.
- PRGA cycles per byte (CPB).

## RC4 Configuration

| Parameter | Value |
|---|---:|
| Algorithm | RC4 |
| Key | `secret_key_for_testing` |
| Key length | 23 bytes |
| State array size | 256 bytes |
| Data size per iteration | 8,192 bytes |
| Number of iterations | 10,000 |
| Total data processed | 81,920,000 bytes |
| Performance measurement | `__rdtsc()` |

## Algorithm Implementation

### 1. Key Scheduling Algorithm (KSA)

The KSA initializes the 256-byte state array and performs a permutation based on the secret key.

The initialization starts with:

```c
for (i = 0; i < 256; i++) {
    state->S[i] = (unsigned char)i;
}
```

The key-dependent permutation is performed using:

```c
j = (j + state->S[i] + key[i % key_len]) % 256;
SWAP(state->S[i], state->S[j]);
```

The program executes KSA 10,000 times and calculates the average CPU cycles.

### 2. Pseudo-Random Generation Algorithm (PRGA)

The PRGA generates pseudorandom keystream bytes using the internal state array.

The generated keystream is XORed with the input data to perform encryption.

```c
unsigned char keystream_byte = rc4_prga_byte(state);
data[k] ^= keystream_byte;
```

The program processes 8,192 bytes per iteration over 10,000 iterations.

## Performance Benchmark Results

The following results were obtained by running the program on my local Windows laptop.

### Hardware Profiling Results

| Metric | Result |
|---|---:|
| Number of iterations | 10,000 |
| Data size per iteration | 8,192 bytes |
| Total bytes processed | 81,920,000 bytes |
| Average KSA CPU cycles | 3,094 cycles |
| PRGA cycles per byte | 14.16 cycles/byte |

### Terminal Output

```text
========================================
Performance Measurements (10000 Iterations)
========================================
Data Size Encrypted per run: 8192 bytes
Total Bytes Encrypted:       81920000 bytes
Average KSA Cycles:          3094 cycles
PRGA Cycles per Byte:        14.16 cycles/byte
========================================
```

## Benchmark Methodology

The program measures KSA and PRGA performance separately using the processor timestamp counter.

### KSA Performance

KSA is executed 10,000 times.

Average KSA CPU cycles are calculated as:

\[
\text{Average KSA Cycles} =
\frac{\text{Total KSA Cycles}}{\text{Number of Iterations}}
\]

For the recorded execution:

\[
\text{Average KSA Cycles} = 3094
\]

### PRGA Performance

PRGA processes 8,192 bytes in each iteration.

Total bytes processed:

\[
8192 \times 10000 = 81,920,000
\]

Cycles per byte are calculated as:

\[
\text{CPB} =
\frac{\text{Total PRGA CPU Cycles}}
{\text{Total Bytes Processed}}
\]

For the recorded execution:

\[
\text{CPB} = 14.16
\]

## How to Compile and Run

### Requirements

- Windows operating system.
- x86/x64 processor.
- GCC compiler (MinGW-w64).
- C source file (`rc4.c`).

The program uses `__rdtsc()` to measure CPU cycles.

For GCC on x86/x64:

```c
#include <x86intrin.h>
```

For Microsoft Visual C (MSVC):

```c
#include <intrin.h>
```

### Compilation

Open a terminal in the directory containing the source file and execute:

```bash
gcc rc4.c -o Rc4.exe
```

### Execution

Run the executable:

```cmd
.\Rc4.exe
```

The program displays the number of iterations, total bytes processed, average KSA cycles, and PRGA cycles per byte.

## Performance Notes

The reported measurements were obtained from one execution on my local laptop.

Actual performance may vary depending on:

- CPU architecture and processor model.
- Compiler and optimization settings.
- Operating system and background processes.
- Measurement overhead.

For more reliable comparisons, conduct multiple benchmark runs, include warm-up iterations, use appropriate serialization around timestamp-counter reads, and record the CPU model, compiler version, and compiler flags.

## Security Note

**RC4 is cryptographically broken and deprecated.**

This implementation is intended for educational purposes, algorithm analysis, and performance benchmarking only.

It should not be used for real-world secure encryption or protection of sensitive information.

## Repository Structure

```text
.
├── rc4.c
└── README.md
```
