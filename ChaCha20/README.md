# ChaCha20 Performance Benchmarking in C

A C implementation of the ChaCha20 stream cipher with hardware performance benchmarking using the x86/x64 timestamp counter (`__rdtsc()`).

This project evaluates the performance of ChaCha20 under different GCC compiler optimization levels (`-O0`, `-O2`, and `-O3`). The benchmark measures CPU cycles, cycles per byte, execution time per iteration, and execution time per byte.

## Overview

This implementation demonstrates:

- ChaCha20 key and state initialization.
- Quarter-round operations.
- Column rounds and diagonal rounds.
- The 20-round ChaCha20 permutation.
- Keystream generation and XOR-based encryption.
- Performance measurement using `__rdtsc()`.
- Execution time measurement using Windows Query Performance Counter.
- Comparison of compiler optimization levels.

## Hardware and Software Specifications

### Processor Information

| Parameter | Specification |
|---|---|
| Processor | Intel Core i5-12450HX |
| Generation | 12th Generation |
| Base Frequency | 2.40 GHz |
| Number of Cores | 8 |
| Logical Processors | 12 |
| L1 Cache | 704 KB |
| L2 Cache | 7 MB |
| L3 Cache | 12 MB |

### Software Environment

| Parameter | Specification |
|---|---|
| Operating System | Windows 11 |
| Compiler | GCC |
| Compiler Version | GCC 6.3.0 (MinGW) |
| Programming Language | C |
| Development Environment | Visual Studio Code |

## Benchmark Configuration

The same input size and number of iterations are used for all three optimization levels.

| Parameter | Value |
|---|---:|
| Algorithm | ChaCha20 |
| Key Size | 256 bits |
| Nonce Size | 64 bits |
| Counter Size | 64 bits |
| Number of Rounds | 20 |
| Message Size | 64 bytes |
| Number of Iterations | 1,000,000 |
| Total Bytes Processed | 64,000,000 bytes |
| Optimization Levels | -O0, -O2, -O3 |

## Compiler Optimization Levels

The benchmark evaluates three GCC optimization levels.

| Optimization | Description |
|---|---|
| -O0 | No compiler optimization |
| -O2 | Moderate compiler optimization |
| -O3 | Aggressive compiler optimization |

All three versions were compiled with the `-msse2` flag to enable SSE2 instructions required by the LFENCE intrinsic used in the benchmark.

## Benchmark Results

The following results were obtained by executing the ChaCha20 implementation on my local laptop.

### Performance Comparison

| Optimization | Cycles/Iteration | Cycles/Byte | Time/Iteration (ns) | Time/Byte (ns) |
|---|---:|---:|---:|---:|
| -O0 | 2789.69 | 43.5888 | 1037.83 | 16.22 |
| -O2 | 840.56 | 13.1338 | 312.71 | 4.89 |
| -O3 | 253.55 | 3.9617 | 94.32 | 1.47 |

### Detailed Results

**1. Optimization Level -O0**

```text
Message Size       : 64 bytes
Iterations         : 1000000
Total Bytes        : 64000000 bytes

Total CPU Cycles   : 2789685697
Cycles/Iteration   : 2789.69
Cycles/Byte        : 43.5888
Time/Iteration     : 1037.83 ns
Time/Byte          : 16.22 ns

Checksum           : 8028
```

**2. Optimization Level -O2**

```text
Message Size       : 64 bytes
Iterations         : 1000000
Total Bytes        : 64000000 bytes

Total CPU Cycles   : 840561098
Cycles/Iteration   : 840.56
Cycles/Byte        : 13.1338
Time/Iteration     : 312.71 ns
Time/Byte          : 4.89 ns

Checksum           : 8028
```

**3. Optimization Level -O3**

```text
Message Size       : 64 bytes
Iterations         : 1000000
Total Bytes        : 64000000 bytes

Total CPU Cycles   : 253547634
Cycles/Iteration   : 253.55
Cycles/Byte        : 3.9617
Time/Iteration     : 94.32 ns
Time/Byte          : 1.47 ns

Checksum           : 8028
```

## Performance Analysis

The benchmark results show a significant improvement in ChaCha20 performance with compiler optimization.

### Comparison of Optimization Levels

- **-O0:** The unoptimized implementation records the highest execution time and CPU cycles.
- **-O2:** Compiler optimization significantly reduces the execution time and cycles per byte.
- **-O3:** The lowest execution time and CPU cycles are observed with aggressive compiler optimization.

### Performance Improvement

Using the measured time per iteration:

| Comparison | Performance Improvement |
|---|---:|
| -O0 to -O2 | 69.85% |
| -O2 to -O3 | 69.83% |
| -O0 to -O3 | 90.90% |

The `-O3` implementation takes approximately 11 times less time per iteration than the `-O0` implementation in this benchmark.

## Benchmark Methodology

The benchmark uses two timing mechanisms.

### 1. CPU Cycle Measurement

The processor timestamp counter is accessed using:

```c
start_cycles = __rdtsc();

/* ChaCha20 encryption */

end_cycles = __rdtsc();
```

Total CPU timestamp-counter ticks:

\[
\text{Total Ticks} = \text{End Timestamp} - \text{Start Timestamp}
\]

Average ticks per iteration:

\[
\text{Ticks/Iteration} =
\frac{\text{Total Ticks}}{\text{Number of Iterations}}
\]

Ticks per byte:

\[
\text{Ticks/Byte} =
\frac{\text{Total Ticks}}{\text{Total Bytes Processed}}
\]

### 2. Execution Time Measurement

Windows Query Performance Counter is used to measure elapsed time.

Time per iteration:

\[
\text{Time/Iteration} =
\frac{\text{Total Execution Time}}{1,000,000}
\]

Time per byte:

\[
\text{Time/Byte} =
\frac{\text{Total Execution Time}}{64,000,000}
\]

## How to Compile and Run

### Requirements

- Windows operating system.
- x86/x64 processor.
- GCC compiler (MinGW-w64).
- Visual Studio Code (optional).

### Compilation

Open the terminal in the directory containing `chacha20.c`.

**Optimization Level -O0:**

```cmd
gcc chacha20.c -o chacha20_O0.exe -O0 -msse2
```

**Optimization Level -O2:**

```cmd
gcc chacha20.c -o chacha20_O2.exe -O2 -msse2
```

**Optimization Level -O3:**

```cmd
gcc chacha20.c -o chacha20_O3.exe -O3 -msse2
```

### Execution

Run each executable separately:

```cmd
.\chacha20_O0.exe
.\chacha20_O2.exe
.\chacha20_O3.exe
```

Each execution displays the CPU cycles, cycles per byte, execution time per iteration, and execution time per byte.

## Performance Notes

The reported measurements were obtained on an Intel Core i5-12450HX processor.

Actual performance may vary depending on:

- Processor architecture and clock frequency.
- Compiler version and optimization settings.
- Operating system and background processes.
- CPU temperature and power management.
- Benchmark measurement overhead.

The results represent measured values from the local machine and should not be treated as universal ChaCha20 performance figures.

For more reliable comparisons, perform multiple independent benchmark runs, include warm-up iterations, and report statistical summaries.

**Note:** `__rdtsc()` measures timestamp-counter ticks, which are not necessarily equivalent to actual CPU core cycles on modern processors.

## Security Note

This project is intended for educational purposes, cryptographic algorithm analysis, and performance benchmarking.

For real-world applications requiring authenticated encryption, use a vetted ChaCha20-Poly1305 implementation.

## Repository Structure

```text
.
├── chacha20.c
└── README.md
```
