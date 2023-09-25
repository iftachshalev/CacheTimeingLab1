#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define TARGET_SIZE 8
#define L1_SIZE 256 * 1024 * 4.5
#define L2_SIZE 2 * 1024 * 1024 * 1.5
#define L3_SIZE 16 * 1024 * 1024 * 1.25
#define CACHE_LINE_SIZE 64

// compile with: gcc -O0 main.c -o main
// run on core 2+

void evict_from_Lx(volatile  uint64_t *eviction_buffer, size_t size, int times);
void fill_buffer(volatile uint64_t *eviction_buffer, size_t size);
void sleep_();
 
int main (int ac, char **av) {

    char name;
    scanf("%c", &name);

    volatile char tmp;
    srand(time(NULL));

    volatile uint64_t *target_buffer = (volatile uint64_t *)malloc(TARGET_SIZE * sizeof(uint64_t));
    volatile uint64_t *eviction_buffer = (volatile uint64_t *)malloc(L1_SIZE * sizeof(uint64_t));

    fill_buffer(target_buffer, TARGET_SIZE);
    fill_buffer(eviction_buffer, L1_SIZE);

    tmp = target_buffer[0];

    for (int i=0; i<SAMPLES*11111111; i++){
        evict_from_Lx(eviction_buffer, L1_SIZE, 2);
        printf("%ld\n", measure_one_block_access_time((uint64_t)target_buffer));
    };
    
    free((uint64_t *)eviction_buffer);
    free((uint64_t *)target_buffer);

    return 0;
}

// LINEAR 
void evict_from_Lx(volatile uint64_t *eviction_buffer, size_t size, int times) {
    int useless = 1;
    for (int j = 0; j < times; j++) {
        for (size_t i = 0; i < size; i++) {
            uint64_t value = eviction_buffer[i];
            useless += value;
        }
    }
}

void fill_buffer(volatile  uint64_t *eviction_buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        eviction_buffer[i] = rand() % 10;
    }
}


void sleep_() {
    long long int n = 2000000000;
    int sum = 0;
    
    clock_t start_time = clock(); // Get the current time before the calculation
    
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    
    clock_t end_time = clock(); // Get the current time after the calculation
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calculate the elapsed time in seconds
    
    printf("Elapsed time: %f seconds\n", elapsed_time);
}
