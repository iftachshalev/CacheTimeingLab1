#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define TARGET_SIZE 8
#define L1_SIZE 256 * 1024 * 1.5
#define L2_SIZE 2 * 1024 * 1024 * 1.5
#define L3_SIZE 16 * 1024 * 1024 * 1.25
#define CACHE_LINE_SIZE 64

// compile with: gcc -O0 main.c -o main
// run on core 2+

void evict_from_Lx(volatile  uint64_t *eviction_buffer, size_t size, int times);
void fill_buffer(volatile uint64_t *eviction_buffer, size_t size);
void sleep_();
// void flush_cache(volatile void* buffer);
 
int main (int ac, char **av) {

    uint64_t dram_latency[SAMPLES] = {0};
    uint64_t l1_latency[SAMPLES] = {0};
    uint64_t l2_latency[SAMPLES] = {0};
    uint64_t l3_latency[SAMPLES] = {0};

    volatile char tmp;
    srand(time(NULL));

    volatile uint64_t *target_buffer = (volatile uint64_t *)malloc(TARGET_SIZE * sizeof(uint64_t));
    volatile uint64_t *eviction_buffer = (volatile uint64_t *)malloc(L1_SIZE * sizeof(uint64_t));
    volatile uint64_t *eviction_buffer2 = (volatile uint64_t *)malloc(L2_SIZE * sizeof(uint64_t));
    volatile uint64_t *eviction_buffer3 = (volatile uint64_t *)malloc(L3_SIZE * sizeof(uint64_t));

    fill_buffer(target_buffer, TARGET_SIZE);
    fill_buffer(eviction_buffer, L1_SIZE);
    fill_buffer(eviction_buffer2, L2_SIZE);
    fill_buffer(eviction_buffer3, L3_SIZE);

    // L1 ====
    for (int i=0; i<SAMPLES; i++){
        tmp = target_buffer[0];

        l1_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
    }

    // L2 ====
    for (int i = 0; i < SAMPLES; i++) {
        evict_from_Lx(eviction_buffer, L1_SIZE, 2);
        // sleep_();
        l2_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
    }

    // L3 ====
    for (int i = 0; i < SAMPLES; i++) {
        evict_from_Lx(eviction_buffer2, L2_SIZE, 4);
        l3_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
    }

    // DRAM ====
    for (int i=0; i<SAMPLES; i++){
        evict_from_Lx(eviction_buffer3, L3_SIZE, 12);
        dram_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
    };

    print_results(dram_latency, l1_latency, l2_latency, l3_latency);

    free((uint64_t *)target_buffer);
    free((uint64_t *)eviction_buffer);
    free((uint64_t *)eviction_buffer2);
    free((uint64_t *)eviction_buffer3);

    char name;
    scanf("%c", &name);
    return 0;
}


// // RANDOM 90% FOR 99% HITS - take a lot of time
// void evict_from_Lx(volatile uint64_t *eviction_buffer, size_t size, int times) {
//     int useless = 1;
//     for (int j = 0; j < times; j++) {
//         for (size_t i = 0; i < size * 5; i++) {
//             uint64_t value = eviction_buffer[rand() % size];
//             if (value == 10) {`x
//                 useless += value;
//             }
//         }
//     }
//     printf("%d", useless);
// }


// LINEAR 
void evict_from_Lx(volatile uint64_t *eviction_buffer, size_t size, int times) {
    int useless = 1;
    for (int j = 0; j < times; j++) {
        for (size_t i = 0; i < size; i++) {
            uint64_t value = eviction_buffer[i];
            useless += value;
        }
    }
    
    // the print below is a necessary sys call for some resone
    if (size <= L2_SIZE) {
        printf("-");
    }
}

void fill_buffer(volatile  uint64_t *eviction_buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        eviction_buffer[i] = rand() % 10;
    }
}


void sleep_() {
    long int n = 180000000;
    int sum = 0;
    
    clock_t start_time = clock(); // Get the current time before the calculation
    
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    
    clock_t end_time = clock(); // Get the current time after the calculation
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calculate the elapsed time in seconds
    
    printf("Elapsed time: %f seconds\n", elapsed_time);
}

// void flush_cache(volatile void* buffer) {
//     char* ptr = (char*)buffer;
//     for (size_t i = 0; i < TARGET_SIZE; i += CACHE_LINE_SIZE) {
//         _mm_clflush(&ptr[i]);
//     }
// }
