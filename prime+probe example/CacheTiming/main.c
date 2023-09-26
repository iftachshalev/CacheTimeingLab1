#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define TARGET_SIZE 8
#define L1_SIZE 256 * 1024 * 1.5
#define L2_SIZE 2 * 1024 * 1024 * 1.5
#define L3_SIZE 16 * 1024 * 1024 * 1.25

 
int main (int ac, char **av) {

    uint64_t dram_latency[SAMPLES] = {0};
    uint64_t l1_latency[SAMPLES] = {0};
    uint64_t l2_latency[SAMPLES] = {0};
    uint64_t l3_latency[SAMPLES] = {0};

    volatile char tmp;
    srand(time(NULL));

    volatile uint64_t *target_buffer = (volatile uint64_t *)malloc(TARGET_SIZE * sizeof(uint64_t)); // exactly cache line size (64)
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
        evict_from_Lx(eviction_buffer, L1_SIZE, 4);
        l2_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
    }

    // L3 ====
    for (int i = 0; i < SAMPLES; i++) {
        // evict_from_Lx(eviction_buffer2, L2_SIZE, 2);
        clflush(target_buffer);  // make sure that clflush doesnt evict the l3 on your mechain before using this.
        l3_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
    }

    // DRAM ====
    for (int i=0; i<SAMPLES; i++){
        evict_from_Lx(eviction_buffer3, L3_SIZE, 12); // on some mechains you can use clflush insted.
        // clflush(target_buffer);
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