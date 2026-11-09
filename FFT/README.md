# FFT and IFFT Implementation & Performance Benchmarking in C

A C implementation of the Fast Fourier Transform (FFT) and Inverse Fast Fourier Transform (IFFT) using the recursive Radix-2 Cooley–Tukey algorithm.

This project evaluates the computational performance of FFT and IFFT under different GCC compiler optimization levels (`-O0`, `-O2`, and `-O3`). The benchmark measures CPU timestamp-counter ticks, cycles per data point, execution time, and reconstruction accuracy for different input sizes.

## Overview

This implementation demonstrates:

- Recursive Radix-2 Cooley–Tukey FFT.
- Inverse Fast Fourier Transform (IFFT).
- Divide-and-conquer approach using even and odd indexed elements.
- Twiddle factor computation using complex exponentials.
- Butterfly operations for combining FFT results.
- Performance measurement using `__rdtsc()`.
- Execution time measurement using Windows QueryPerformanceCounter.
- Comparison of compiler optimization levels.
- Numerical accuracy verification using reconstruction error.

## Algorithm Description

### 1. Fast Fourier Transform (FFT)

The FFT converts a sequence from the time domain into its frequency-domain representation.

This implementation uses the Radix-2 Cooley–Tukey algorithm, which recursively divides the input into two subsequences:

- Even-indexed elements.
- Odd-indexed elements.

The two subsequences are transformed recursively and combined using butterfly operations.

The mathematical formulation is:

\[
X[k] = E[k] + W_N^k O[k]
\]

\[
X[k+N/2] = E[k] - W_N^k O[k]
\]

Where:

- \(E[k]\) represents the FFT of even-indexed elements.
- \(O[k]\) represents the FFT of odd-indexed elements.
- \(W_N^k = e^{2\pi i k/N}\) is the twiddle factor.

### 2. Inverse Fast Fourier Transform (IFFT)

The IFFT reconstructs the original time-domain sequence from its frequency-domain representation.

It uses the negative exponential:

\[
W_N^k = e^{-2\pi i k/N}
\]

After the recursive transformation, each output element is divided by \(N\):

\[
x[n] = \frac{1}{N}
\sum_{k=0}^{N-1}
X[k]e^{-2\pi i kn/N}
\]

The implementation verifies the reconstruction by comparing the original input with the reconstructed output.

## Computational Complexity

The Radix-2 Cooley–Tukey algorithm has the following time complexity:

\[
T(N) = O(N\log_2 N)
\]

This is more efficient than the direct Discrete Fourier Transform (DFT), which has a computational complexity of:

\[
T(N) = O(N^2)
\]

Both FFT and IFFT use the recursive divide-and-conquer approach.

## Hardware and Software Specifications

### Processor Information

| Parameter | Specification |
|---|---|
| Processor | 12th Gen Intel Core i5-12450HX |
| Processor Base Frequency | 2.40 GHz |
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
| Mathematical Library | libm |

## Benchmark Configuration

The FFT and IFFT implementations were evaluated using different input sizes and compiler optimization levels.

| Parameter | Value |
|---|---|
| Algorithm | Radix-2 Cooley–Tukey FFT |
| Input Sizes (N) | 64, 128, 256, 512, 1024, 2048 |
| Iterations per Input Size | 1,000 |
| Optimization Levels | -O0, -O2, -O3 |
| CPU Cycle Measurement | `__rdtsc()` |
| Execution Time Measurement | QueryPerformanceCounter |
| Input Data Type | Double Complex |

All input sizes are powers of two, as required by this Radix-2 implementation.

## Compiler Optimization Levels

Three GCC optimization levels were used to evaluate the effect of compiler optimization on computational performance.

| Optimization | Description |
|---|---|
| -O0 | No compiler optimization |
| -O2 | Moderate compiler optimization |
| -O3 | Aggressive compiler optimization |

All three versions were compiled using the `-msse2` flag.

# Experimental Results

The following results were obtained by executing the FFT and IFFT benchmarking program on my local laptop.

## 1. FFT Performance Results

### Optimization Level -O0

| Input Size (N) | Cycles/Iteration | Cycles/Point | Time/Iteration (ns) | Time/Point (ns) |
|---:|---:|---:|---:|---:|
| 64 | 46,003.42 | 718.8034 | 17,109.90 | 267.3422 |
| 128 | 93,828.81 | 733.0376 | 34,906.30 | 272.7055 |
| 256 | 258,015.74 | 1,007.8740 | 95,987.40 | 374.9508 |
| 512 | 385,070.64 | 752.0911 | 143,255.00 | 279.7949 |
| 1024 | 811,864.71 | 792.8366 | 302,032.30 | 294.9534 |
| 2048 | 1,706,632.41 | 833.3166 | 634,906.80 | 310.0131 |

### Optimization Level -O2

| Input Size (N) | Cycles/Iteration | Cycles/Point | Time/Iteration (ns) | Time/Point (ns) |
|---:|---:|---:|---:|---:|
| 64 | 28,471.42 | 444.8659 | 10,589.20 | 165.4563 |
| 128 | 72,881.31 | 569.3853 | 27,113.30 | 211.8227 |
| 256 | 145,542.40 | 568.5250 | 54,144.80 | 211.5031 |
| 512 | 297,547.07 | 581.1466 | 110,693.90 | 216.1990 |
| 1024 | 603,925.33 | 589.7708 | 224,673.90 | 219.4081 |
| 2048 | 1,270,240.10 | 620.2344 | 472,558.50 | 230.7415 |

### Optimization Level -O3

| Input Size (N) | Cycles/Iteration | Cycles/Point | Time/Iteration (ns) | Time/Point (ns) |
|---:|---:|---:|---:|---:|
| 64 | 32,013.66 | 500.2134 | 11,906.80 | 186.0437 |
| 128 | 74,862.00 | 584.8594 | 27,850.10 | 217.5789 |
| 256 | 141,322.48 | 552.0410 | 52,574.90 | 205.3707 |
| 512 | 290,052.54 | 566.5089 | 107,906.10 | 210.7541 |
| 1024 | 630,862.81 | 616.0770 | 234,695.10 | 229.1944 |
| 2048 | 1,299,755.15 | 634.6461 | 483,539.20 | 236.1031 |

## 2. IFFT Performance Results

### Optimization Level -O0

| Input Size (N) | Cycles/Iteration | Cycles/Point | Time/Iteration (ns) | Time/Point (ns) |
|---:|---:|---:|---:|---:|
| 64 | 45,838.14 | 716.2210 | 17,052.60 | 266.4469 |
| 128 | 90,392.25 | 706.1895 | 33,627.80 | 262.7172 |
| 256 | 183,673.93 | 717.4763 | 68,330.70 | 266.9168 |
| 512 | 392,067.32 | 765.7565 | 145,857.60 | 284.8781 |
| 1024 | 818,485.13 | 799.3019 | 304,495.30 | 297.3587 |
| 2048 | 1,723,465.42 | 841.5359 | 641,168.70 | 313.0707 |

### Optimization Level -O2

| Input Size (N) | Cycles/Iteration | Cycles/Point | Time/Iteration (ns) | Time/Point (ns) |
|---:|---:|---:|---:|---:|
| 64 | 29,198.69 | 456.2295 | 10,862.10 | 169.7203 |
| 128 | 77,518.43 | 605.6127 | 28,838.20 | 225.2984 |
| 256 | 144,316.31 | 563.7356 | 53,688.80 | 209.7219 |
| 512 | 289,922.78 | 566.2554 | 107,857.80 | 210.6598 |
| 1024 | 670,171.20 | 654.4641 | 249,318.80 | 243.4754 |
| 2048 | 1,278,447.56 | 624.2420 | 475,611.50 | 232.2322 |

### Optimization Level -O3

| Input Size (N) | Cycles/Iteration | Cycles/Point | Time/Iteration (ns) | Time/Point (ns) |
|---:|---:|---:|---:|---:|
| 64 | 29,440.11 | 460.0018 | 10,952.10 | 171.1266 |
| 128 | 71,922.60 | 561.8953 | 26,756.60 | 209.0359 |
| 256 | 209,251.92 | 817.3903 | 77,846.30 | 304.0871 |
| 512 | 293,474.72 | 573.1928 | 109,179.00 | 213.2402 |
| 1024 | 616,623.27 | 602.1712 | 229,398.00 | 224.0215 |
| 2048 | 1,295,805.56 | 632.7176 | 482,069.70 | 235.3856 |

## 3. Numerical Accuracy Verification

The IFFT implementation was used to reconstruct the original input after applying FFT.

The maximum absolute reconstruction error was calculated as:

\[
E_{\max} =
\max_{0\leq i<N}
|x[i]-\hat{x}[i]|
\]

### Reconstruction Error Results

| Input Size (N) | Maximum Reconstruction Error |
|---:|---:|
| 64 | 0.000000000000 |
| 128 | 0.000000000000 |
| 256 | 0.000000000001 |
| 512 | 0.000000000004 |
| 1024 | 0.000000000024 |
| 2048 | 0.000000000049 |

The reconstruction errors are very small and consistent with floating-point numerical precision.

This confirms that the FFT and IFFT operations successfully reconstruct the original input for the tested sizes.

**Note:** The reconstruction errors are the same across the three optimization levels in the recorded runs.

# Performance Analysis

## 1. Effect of Compiler Optimization

The benchmark results demonstrate that compiler optimization has a significant impact on FFT and IFFT execution time.

- **-O0:** The unoptimized implementation generally records higher execution times and CPU timestamp-counter ticks.
- **-O2:** Compiler optimization reduces execution time for most tested input sizes.
- **-O3:** Aggressive optimization produces results that are competitive with -O2, although it does not consistently outperform -O2 for every input size.

## 2. Effect of Input Size

As the input size increases, the total execution time also increases.

For the FFT implementation, the execution time increases from approximately 17.11 microseconds for N = 64 to 634.91 microseconds for N = 2048 under -O0.

The observed scaling is consistent with the expected computational complexity of the Radix-2 FFT:

\[
O(N\log_2 N)
\]

## 3. FFT and IFFT Comparison

Both FFT and IFFT use the same recursive divide-and-conquer structure.

However, their measured execution times differ slightly because of differences in the twiddle factors and additional normalization performed by IFFT.

The benchmark evaluates both operations independently to understand their computational costs.

# Benchmark Methodology

Two timing mechanisms are used in the benchmarking program.

## 1. CPU Timestamp Counter

The `__rdtsc()` intrinsic reads the processor timestamp counter.

```c
_mm_lfence();
start_cycles = __rdtsc();
_mm_lfence();

/* FFT or IFFT execution */

_mm_lfence();
end_cycles = __rdtsc();
```

Total timestamp-counter ticks:

\[
C_{\text{total}} =
C_{\text{end}}-C_{\text{start}}
\]

Average ticks per iteration:

\[
C_{\text{iteration}} =
\frac{C_{\text{total}}}{1000}
\]

Ticks per data point:

\[
C_{\text{point}} =
\frac{C_{\text{total}}}{1000N}
\]

## 2. Execution Time Measurement

Windows QueryPerformanceCounter is used to measure elapsed execution time.

Average execution time per iteration:

\[
T_{\text{iteration}} =
\frac{T_{\text{total}}}{1000}
\]

Execution time per data point:

\[
T_{\text{point}} =
\frac{T_{\text{total}}}{1000N}
\]

The execution time is reported in nanoseconds.

# How to Compile and Run

## Requirements

- Windows operating system.
- x86/x64 processor.
- GCC compiler (MinGW-w64).
- C compiler supporting C99 or later.
- Windows QueryPerformanceCounter API.

## Compilation

Open the terminal in the directory containing `fft.c`.

### Optimization Level -O0

```cmd
gcc fft.c -o fft_O0.exe -O0 -msse2 -lm
```

### Optimization Level -O2

```cmd
gcc fft.c -o fft_O2.exe -O2 -msse2 -lm
```

### Optimization Level -O3

```cmd
gcc fft.c -o fft_O3.exe -O3 -msse2 -lm
```

## Execution

Run each executable separately:

```cmd
.\fft_O0.exe
```

```cmd
.\fft_O2.exe
```

```cmd
.\fft_O3.exe
```

Each execution produces separate FFT and IFFT performance tables for all six input sizes.

# Performance Measurement Notes

The reported measurements were obtained from one benchmark execution per optimization level on the local laptop.

Actual performance can vary depending on:

- Processor architecture and clock frequency.
- Compiler version and optimization settings.
- Operating system and background processes.
- CPU temperature and power management.
- Memory allocation and function-call overhead.
- Measurement overhead.

The `__rdtsc()` instruction measures timestamp-counter ticks, which are not necessarily equivalent to actual CPU core cycles on modern processors.

For more reliable performance comparisons, perform multiple independent benchmark runs, use warm-up iterations, and report median execution times.

# Conclusion

This project implements recursive Radix-2 Cooley–Tukey FFT and IFFT algorithms in C and evaluates their performance under three GCC compiler optimization levels.

The experiment examines the effect of compiler optimization and input size on computational performance.

The numerical reconstruction results also demonstrate that the inverse transformation successfully recovers the original input with very small floating-point errors.

## Repository Structure

```text
.
├── fft.c
└── README.md
```
