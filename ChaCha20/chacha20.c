#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>

// Include the header for x86/x64 hardware intrinsics like __rdtsc()
#if defined(_MSC_VER)
    #include <intrin.h>
#else
    #include <x86intrin.h>
#endif

#define ROTL32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))


void quarter_round(uint32_t *state, int a, int b, int c, int d) {
    state[a] += state[b]; state[d] ^= state[a]; state[d] = ROTL32(state[d], 16);
    state[c] += state[d]; state[b] ^= state[c]; state[b] = ROTL32(state[b], 12);
    state[a] += state[b]; state[d] ^= state[a]; state[d] = ROTL32(state[d], 8);
    state[c] += state[d]; state[b] ^= state[c]; state[b] = ROTL32(state[b], 7);
}

void column_round(uint32_t *state) {
    quarter_round(state, 0, 4, 8, 12);
    quarter_round(state, 1, 5, 9, 13);
    quarter_round(state, 2, 6, 10, 14);
    quarter_round(state, 3, 7, 11, 15);
}

void diagonal_round(uint32_t *state) {
    quarter_round(state, 0, 5, 10, 15);
    quarter_round(state, 1, 6, 11, 12);
    quarter_round(state, 2, 7, 8, 13);
    quarter_round(state, 3, 4, 9, 14);
}

void permute(uint32_t *state) {
	int i;
    for (i = 0; i < 10; i++) {
        column_round(state);
        diagonal_round(state);
    }
}

void increment_counter(uint32_t *state) {
    if (++state[12] == 0) {
        ++state[13];
    }
}

void chacha20_init(uint32_t *state, const uint8_t *key, const uint8_t *nonce, uint64_t counter) {
	int i;
    state[0] = 0x61707865;
    state[1] = 0x3320646E;
    state[2] = 0x79622D32;
    state[3] = 0x6B206574;

    for (i = 0; i < 8; i++) {
        state[4 + i] = ((uint32_t)key[i*4]) | 
                       (((uint32_t)key[i*4 + 1]) << 8) | 
                       (((uint32_t)key[i*4 + 2]) << 16) | 
                       (((uint32_t)key[i*4 + 3]) << 24);
    }

    state[12] = (uint32_t)(counter & 0xFFFFFFFF);
    state[13] = (uint32_t)(counter >> 32);

    state[14] = ((uint32_t)nonce[0]) | (((uint32_t)nonce[1]) << 8) | 
                (((uint32_t)nonce[2]) << 16) | (((uint32_t)nonce[3]) << 24);
                
    state[15] = ((uint32_t)nonce[4]) | (((uint32_t)nonce[5]) << 8) | 
                (((uint32_t)nonce[6]) << 16) | (((uint32_t)nonce[7]) << 24);
}

void chacha20_encrypt(uint32_t *initial_state, const uint8_t *in, uint8_t *out, size_t len) {
    uint32_t state[16];
    uint8_t keystream[64];
    size_t i, j;

    for (i = 0; i < len; i += 64) {
        memcpy(state, initial_state, sizeof(state));
        permute(state);

        for (j = 0; j < 16; j++) {
            state[j] += initial_state[j];
        }

        for (j = 0; j < 16; j++) {
            keystream[j*4]     = (uint8_t)(state[j]);
            keystream[j*4 + 1] = (uint8_t)(state[j] >> 8);
            keystream[j*4 + 2] = (uint8_t)(state[j] >> 16);
            keystream[j*4 + 3] = (uint8_t)(state[j] >> 24);
        }

        size_t block_len = (len - i) < 64 ? (len - i) : 64;
        for (j = 0; j < block_len; j++) {
            out[i + j] = in[i + j] ^ keystream[j];
        }

        increment_counter(initial_state);
    }
}



int main() {
    uint8_t key[32] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38
    };

    uint8_t nonce[8] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01
    };

    #define MESSAGE_SIZE 64
    #define ITERATIONS 1000000

    uint8_t input[MESSAGE_SIZE];
    uint8_t output[MESSAGE_SIZE];

    uint32_t state[16];

    int i;

    // Initialize a fixed 64-byte input
    for (i = 0; i < MESSAGE_SIZE; i++) {
        input[i] = (uint8_t)i;
    }

    // Initialize ChaCha20 state
    chacha20_init(state, key, nonce, 1);

    // Variables for performance measurement
    uint64_t start_cycles, end_cycles;
    uint64_t total_cycles;

    LARGE_INTEGER frequency;
    LARGE_INTEGER start_time, end_time;

    QueryPerformanceFrequency(&frequency);

    // Hardware cycle measurement
    _mm_lfence();
    start_cycles = __rdtsc();
    _mm_lfence();

    // Wall-clock time measurement
    QueryPerformanceCounter(&start_time);

    // Perform encryption 1,000,000 times
    for (i = 0; i < ITERATIONS; i++) {
        chacha20_encrypt(
            state,
            input,
            output,
            MESSAGE_SIZE
        );
    }

    QueryPerformanceCounter(&end_time);

    _mm_lfence();
    end_cycles = __rdtsc();

    total_cycles = end_cycles - start_cycles;

    // Prevent the output from being discarded
    volatile uint64_t checksum = 0;

    for (i = 0; i < MESSAGE_SIZE; i++) {
        checksum += output[i];
    }

    // Calculate total bytes processed
    uint64_t total_bytes =
        (uint64_t)MESSAGE_SIZE * ITERATIONS;

    // Calculate benchmark metrics
    double elapsed_seconds =
        (double)(end_time.QuadPart - start_time.QuadPart)
        / frequency.QuadPart;

    double cycles_per_iteration =
        (double)total_cycles / ITERATIONS;

    double cycles_per_byte =
        (double)total_cycles / total_bytes;

    double time_per_iteration =
        (elapsed_seconds * 1e9) / ITERATIONS;

    double time_per_byte =
        (elapsed_seconds * 1e9) / total_bytes;

    // Display results
    printf("\n========================================\n");
    printf("       ChaCha20 Performance Benchmark\n");
    printf("========================================\n");

    printf("Message Size       : %d bytes\n", MESSAGE_SIZE);
    printf("Iterations         : %d\n", ITERATIONS);
    printf("Total Bytes        : %llu bytes\n",
           (unsigned long long)total_bytes);

    printf("\n--- RESULTS ---\n");

    printf("Total CPU Cycles   : %llu\n",
           (unsigned long long)total_cycles);

    printf("Cycles/Iteration   : %.2f\n",
           cycles_per_iteration);

    printf("Cycles/Byte        : %.4f\n",
           cycles_per_byte);

    printf("Time/Iteration     : %.2f ns\n",
           time_per_iteration);

    printf("Time/Byte          : %.2f ns\n",
           time_per_byte);

    printf("\nChecksum           : %llu\n",
           (unsigned long long)checksum);

    printf("========================================\n");

    return 0;
}
