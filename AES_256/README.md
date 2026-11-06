
# AES-256 Encryption and Decryption in C

A C implementation of **AES-256** that performs encryption and decryption on a 128-bit data block and measures execution time in CPU cycles using the x86 `RDTSC` instruction.

## Overview

This program demonstrates:

- AES-256 encryption and decryption.
- AES key expansion (round-key generation).
- The AES transformations: SubBytes, ShiftRows, MixColumns, and AddRoundKey.
- Inverse transformations for decryption.
- A performance benchmark over 10,000 iterations.
- Average CPU cycles and cycles per byte (CPB) for encryption and decryption.

## AES Configuration

| Parameter | Value |
|---|---:|
| Algorithm | AES-256 |
| Key size | 256 bits (32 bytes) |
| Block size | 128 bits (16 bytes) |
| Number of rounds | 14 |
| Number of 32-bit key words (Nk) | 8 |
| Number of state columns (Nb) | 4 |
| Benchmark iterations | 10,000 |

**Note:** AES-256 refers to the 256-bit key size. AES always uses a 128-bit block size.

## Test Input

The program uses the following 256-bit key and 128-bit plaintext.

### AES-256 Key (32 bytes)

```text
60 3d eb 10 15 ca 71 be 2b 73 ae f0 85 7d 77 81
1f 35 2c 07 3b 61 08 d7 2d 98 10 a3 09 14 df f4
```

### Plaintext (16 bytes)

```text
6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a
```

## Results Obtained

The following results were obtained by running the program on my local Windows PC.

### Encryption Results

**Ciphertext:**

```text
f3 ee d1 bd b5 d2 a0 3c 06 4b 5a 7e 3d b1 81 f8
```

| Metric | Result |
|---|---:|
| Average encryption CPU cycles (10,000 runs) | 2,620.36 |
| Encryption cycles per byte (CPB) | 163.77 |

### Decryption Results

**Decrypted plaintext:**

```text
6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a
```

| Metric | Result |
|---|---:|
| Average decryption CPU cycles (10,000 runs) | 3,877.61 |
| Decryption cycles per byte (CPB) | 242.35 |

### Performance Summary

| Operation | Average CPU cycles | Cycles per byte |
|---|---:|---:|
| Encryption | 2,620.36 | 163.77 |
| Decryption | 3,877.61 | 242.35 |

The decrypted plaintext matches the original input plaintext, confirming that the encryption and decryption operations work correctly for this test vector.

## How to Compile and Run

### Requirements

- Windows operating system.
- x86/x64 processor.
- GCC compiler (MinGW-w64).
- C source file (`aes.c`).

The program uses `__rdtsc()` to measure CPU cycles. For GCC on x86/x64, include:

```c
#include <x86intrin.h>
```

### Compilation

Open the terminal in the directory containing `aes.c` and execute:

```bash
gcc aes.c -o aes.exe
```

### Execution

Run the executable:

```cmd
.\aes.exe
```

The program displays the input key, plaintext, ciphertext, decrypted plaintext, average CPU cycles, and cycles per byte.

## Benchmark Methodology

The program performs encryption and decryption 10,000 times and measures the timestamp-counter difference using `__rdtsc()`.

Average CPU cycles are calculated as:

\[
\text{Average CPU Cycles} =
\frac{\text{Total Measured CPU Cycles}}{10,000}
\]

Since AES processes one 16-byte block:

\[
\text{Cycles Per Byte (CPB)} =
\frac{\text{Average CPU Cycles}}{16}
\]

For the recorded execution:

- Encryption: 2620.36 / 16 = 163.77 CPB.
- Decryption: 3877.61 / 16 = 242.35 CPB.

## Performance Notes

These measurements represent one execution on my local PC. Actual performance may vary depending on:

- CPU architecture and processor model.
- Compiler and optimization flags.
- Operating system and background processes.
- Measurement overhead.

For more reliable performance comparisons, conduct multiple benchmark runs, use warm-up iterations, and apply appropriate serialization around timestamp-counter measurements.

## Repository Structure

```text
.
├── aes.c
└── README.md
```

## License

No specific license is declared for this project. Add a LICENSE file if you intend to distribute or reuse the code.
