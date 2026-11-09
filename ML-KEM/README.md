# ML-KEM: C Implementation

A C implementation of the Module-Lattice-Based Key-Encapsulation Mechanism (ML-KEM), supporting ML-KEM-512, ML-KEM-768, and ML-KEM-1024.

This project implements the core operations of ML-KEM, including key generation, encapsulation, decapsulation, polynomial arithmetic, Number Theoretic Transform (NTT), and cryptographic hash functions.

## 1. Overview

ML-KEM is a post-quantum key-encapsulation mechanism standardized by NIST in FIPS 203.

It allows two parties to establish a shared secret over a public communication channel without directly transmitting the secret.

The implementation includes:

- Key generation
- Encapsulation
- Decapsulation
- Implicit rejection for invalid ciphertexts
- Polynomial arithmetic
- Number Theoretic Transform (NTT)
- SHA3 and SHAKE operations
- Functional testing
- Performance benchmarking

**Note:** This is an educational and experimental implementation. Passing the included tests does not establish full FIPS 203 conformance or security certification.

## 2. Supported Parameter Sets

| Parameter Set | Public Key | Private Key | Ciphertext | Shared Secret |
|---|---:|---:|---:|---:|
| ML-KEM-512 | 800 bytes | 1632 bytes | 768 bytes | 32 bytes |
| ML-KEM-768 | 1184 bytes | 2400 bytes | 1088 bytes | 32 bytes |
| ML-KEM-1024 | 1568 bytes | 3168 bytes | 1568 bytes | 32 bytes |

## 3. Project Structure

```text
ML-KEM/
│
├── Makefile
├── params.c
├── params.h
├── crypto.c
├── crypto.h
├── general.c
├── general.h
├── ntt.c
├── ntt.h
├── ntt_tables.h
├── kpke.c
├── kpke.h
├── mlkem.c
├── mlkem.h
├── demo.c
├── test.c
├── bench.c
├── bench_time.c
└── README.md
```

### Main Components

| File | Description |
|---|---|
| `params.c`, `params.h` | ML-KEM parameter definitions |
| `crypto.c`, `crypto.h` | Keccak, SHA3, SHAKE, PRF and random number generation |
| `general.c`, `general.h` | Encoding, decoding, compression, decompression and sampling |
| `ntt.c`, `ntt.h` | NTT, inverse NTT and polynomial arithmetic |
| `ntt_tables.h` | Precomputed NTT constants |
| `kpke.c`, `kpke.h` | Internal public-key encryption and decryption operations |
| `mlkem.c`, `mlkem.h` | ML-KEM key generation, encapsulation and decapsulation |
| `demo.c` | ML-KEM-768 demonstration |
| `test.c` | Functional and arithmetic tests |
| `bench.c` | TSC-based performance benchmark |
| `bench_time.c` | Wall-clock performance benchmark |

## 4. Requirements

The project was built and tested using:

- Ubuntu on WSL2
- GCC 15.2.0
- GNU Make 4.4.1
- C11

The implementation uses POSIX-specific features such as `/dev/urandom` and `clock_gettime`. Therefore, Linux or WSL2 is recommended.

## 5. Build and Run

### Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/ML-KEM.git
cd ML-KEM
```

### Compile and run tests

```bash
make test
```

### Run the demonstration

```bash
make demo
```

### Run the TSC-based benchmark

```bash
make bench
```

### Run the wall-clock benchmark

```bash
make bench_time
```

### Clean generated binaries

```bash
make clean
```

## 6. Testing

The test suite includes:

- SHA3-256 and SHA3-512 known-answer tests.
- SHAKE128 and SHAKE256 known-answer tests.
- NTT multiplication compared against schoolbook polynomial multiplication.
- NTT inverse round-trip testing.
- ByteEncode and ByteDecode round-trip testing.
- Compression and decompression error-bound testing.
- ML-KEM key generation, encapsulation and decapsulation.
- Ciphertext tampering and implicit rejection.
- Malformed encapsulation key rejection.

The current test suite successfully completed:

- 100 key-exchange cycles for ML-KEM-512.
- 100 key-exchange cycles for ML-KEM-768.
- 100 key-exchange cycles for ML-KEM-1024.

All included tests passed.

## 7. Demonstration

The ML-KEM-768 demonstration successfully generated a shared secret for both sender and receiver.

Example output:

```text
ML-KEM-768  ek=1184 dk=2400 ct=1088 bytes

sender   K = [32-byte shared secret]
receiver K = [same 32-byte shared secret]

MATCH
```

Both parties successfully derived the same 32-byte shared secret.

## 8. Performance Benchmarks

Benchmarks were performed using GCC with `-O3 -march=native`.

### Wall-clock benchmark

Median execution time over 201 samples:

| Operation | ML-KEM-512 | ML-KEM-768 | ML-KEM-1024 |
|---|---:|---:|---:|
| Key Generation | 38.72 µs | 62.91 µs | 88.39 µs |
| Encapsulation | 39.85 µs | 62.33 µs | 89.85 µs |
| Decapsulation | 50.54 µs | 76.10 µs | 108.96 µs |

### Component benchmarks

| Component | Median Execution Time |
|---|---:|
| NTT | 1.23 µs |
| Inverse NTT | 1.22 µs |
| MultiplyNTTs | 0.12 µs |
| SampleNTT | 2.02 µs |
| SamplePolyCBD (eta=2) | 0.96 µs |
| PRF (SHAKE256) | 0.65 µs |
| ByteEncode (d=12) | 2.76 µs |
| Polynomial Compression (d=10) | 0.05 µs |
| SHA3-256 | 5.67 µs |
| SHA3-512 | 0.73 µs |

### TSC-based benchmark

A separate benchmark measures TSC ticks as an approximate cycle-related performance metric.

These measurements depend on processor frequency, hardware, operating system scheduling and virtualization overhead. They should not be interpreted as guaranteed CPU cycles.

## 9. Future Improvements

- Validate the implementation against official NIST ML-KEM test vectors.
- Conduct a detailed cryptographic security review.
- Improve constant-time implementation and side-channel resistance.
- Optimize polynomial arithmetic and Keccak operations.
- Compare performance against established ML-KEM libraries.
- Add automated testing and continuous integration.

## 10. References

- [NIST FIPS 203: Module-Lattice-Based Key-Encapsulation Mechanism](https://csrc.nist.gov/pubs/fips/203/final)
- [NIST Post-Quantum Cryptography Project](https://csrc.nist.gov/projects/post-quantum-cryptography)
