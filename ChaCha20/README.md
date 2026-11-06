# ChaCha20 Encryption and Decryption in C

A C implementation of the ChaCha20 stream cipher with hardware performance profiling using the x86/x64 timestamp counter (`__rdtsc()`).

The program accepts a message from the user, encrypts it, displays the ciphertext in hexadecimal, measures the CPU cycles required for encryption, and decrypts the ciphertext to verify the original message.

## Overview

This implementation demonstrates:

- ChaCha20 key and state initialization.
- ChaCha20 quarter-round operation.
- Column rounds and diagonal rounds.
- The 20-round ChaCha20 permutation.
- Keystream generation and XOR-based encryption.
- Decryption using the same XOR operation.
- Hardware performance measurement using `__rdtsc()`.
- CPU cycles and cycles per byte (CPB) calculation.

## ChaCha20 Configuration

| Parameter | Value |
|---|---:|
| Algorithm | ChaCha20 |
| Key size | 256 bits (32 bytes) |
| Nonce size | 64 bits (8 bytes) |
| Counter size | 64 bits |
| Number of rounds | 20 |
| State size | 512 bits |
| Keystream block size | 512 bits (64 bytes) |
| Performance measurement | `__rdtsc()` |

**Note:** This implementation uses the original ChaCha20 state layout with a 64-bit counter and a 64-bit nonce. It is different from the IETF ChaCha20 variant, which uses a 32-bit counter and a 96-bit nonce.

## Test Configuration

### Key (32 bytes)

```text
01 02 03 04 05 06 07 08
11 12 13 14 15 16 17 18
21 22 23 24 25 26 27 28
31 32 33 34 35 36 37 38
```

### Nonce (8 bytes)

```text
00 00 00 00 00 00 00 01
```

### Initial Counter

```text
1
```

### Input Message

```text
I love Machine Learning
```

Message length: **23 bytes**

## Results Obtained

The following results were obtained by running the program on my local Windows laptop.

### Hardware Profiling Results

| Metric | Result |
|---|---:|
| Message length | 23 bytes |
| CPU cycles | 4,620 |
| Cycles per byte (CPB) | 200.87 |

### Encryption Result

**Ciphertext (HEX):**

```text
6A 26 A0 49 29 3C 69 67 4E B2 E3 63 48 4D 60 41
E1 C8 9C 7D 4D D4 44
```

### Decryption Result

**Decrypted message:**

```text
I love Machine Learning
```

The decrypted message matches the original input message, confirming that encryption and decryption work correctly for this test run.

## How to Compile and Run

### Requirements

- Windows operating system.
- x86/x64 processor.
- GCC compiler (MinGW-w64).
- C source file (`chacha20.c`).

The code uses `__rdtsc()` to read the processor timestamp counter.

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
gcc chacha20.c -o chacha20.exe
```

### Execution

Run the executable:

```cmd
.\chacha20.exe
```

Enter a message when prompted. The program displays the message length, CPU cycles, cycles per byte, ciphertext, and decrypted message.

## Benchmark Methodology

The program measures the timestamp-counter value immediately before and after the encryption operation.

Total CPU cycles:

\[
\text{CPU Cycles} = \text{End Timestamp} - \text{Start Timestamp}
\]

Cycles per byte:

\[
\text{CPB} = \frac{\text{Total CPU Cycles}}{\text{Message Length in Bytes}}
\]

For the recorded execution:

\[
\text{CPB} = \frac{4620}{23} \approx 200.87
\]

## Performance Notes

The reported values are from one execution on my local laptop. Actual performance may vary depending on:

- CPU architecture and processor model.
- Compiler and optimization settings.
- Operating system and background processes.
- Measurement overhead.

For more reliable comparisons, conduct multiple benchmark runs, include warm-up iterations, use appropriate serialization around timestamp-counter reads, and record the CPU model, compiler version, and compiler flags.

## Security Notes

- This program uses a fixed key and nonce for demonstration purposes.
- Never reuse the same key and nonce pair for different messages in real applications.
- ChaCha20 provides confidentiality but does not authenticate ciphertext.
- For practical security applications, use a vetted ChaCha20-Poly1305 implementation.

This is an educational implementation and should be reviewed and tested before security-sensitive use.

## Repository Structure

```text
.
├── chacha20.c
└── README.md
```
