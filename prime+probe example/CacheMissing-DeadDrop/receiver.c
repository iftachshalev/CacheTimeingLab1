#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define TARGET_SIZE 8
#define L1_SIZE 256 * 1024 * 1.5
#define L2_SIZE 2 * 1024 * 1024 * 1.5
#define L3_SIZE 16 * 1024 * 1024 * 1.25

void sleep_();
void print_l1_results(uint64_t* l1);
 

int main (int ac, char **av) {

    uint64_t l1_latency[SAMPLES] = {0};
    volatile char tmp;    
    volatile uint64_t *target_buffer = (volatile uint64_t *)malloc(TARGET_SIZE * sizeof(uint64_t)); // exactly cache line size (64)

    fill_buffer(target_buffer, TARGET_SIZE);
    
    sleep(5.5);
    printf("\nreceiving bit...\n");

    for (int i=0; i<SAMPLES; i++){
        tmp = target_buffer[0];
        sleep_();
        l1_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
    }

    print_l1_results(l1_latency);  // use this line to see the actual l1 latencys 

    int bit = 0;
    if (l1_latency[SAMPLES/2 + 30] > 60) {  // [SAMPLES/2 + 30] has to be change according to SAMPLES. corrently set for SAMPLES=100
        bit = 1;
    }
    printf("\nthe bit is: %d\n\n", bit);

    free((uint64_t *)target_buffer);

    return 0;
}


void sleep_() {
    long long int n = 1500000;
    int sum = 0;
    
    clock_t start_time = clock();
    
    for (int i = 1; i <= n; i++) {
        sum *= i;
        sum /= i;
    }
    
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    // printf("Elapsed time: %f seconds\n", elapsed_time);
}


void print_l1_results(uint64_t* l1) {
    qsort(l1, SAMPLES, sizeof(uint64_t), compare);

    print_array("L1", l1);

    printf("\nmemory type  :    L1\n");
    printf("----------------------\n");
    printf("Minimum      : %5ld\n", l1[0]);

    printf("Bottom decile: %5ld\n", l1[SAMPLES/10]);

    printf("Median       : %5ld\n", l1[SAMPLES/2]);

    printf("Top decile   : %5ld\n", l1[(SAMPLES * 9)/10]);

    printf("Maximum      : %5ld\n", l1[SAMPLES-1]);
}


