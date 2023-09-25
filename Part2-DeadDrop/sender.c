#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <unistd.h>

#define TARGET_SIZE 8
#define L1_SIZE 256 * 1024 * 4.5

// compile with: gcc -O0 main.c -o main
// run on core 2+

void evict_from_Lx(volatile  uint64_t *eviction_buffer, size_t size, int times);
void fill_buffer(volatile uint64_t *eviction_buffer, size_t size);
int getInputAfterDelay();
 
int main (int ac, char **av) {

    int bit = getInputAfterDelay();
    printf("sending bit...\n");

    int sec = 2;

    if (bit == 1) {
        volatile char tmp;
        srand(time(NULL));

        volatile uint64_t *target_buffer = (volatile uint64_t *)malloc(TARGET_SIZE * sizeof(uint64_t));
        volatile uint64_t *eviction_buffer = (volatile uint64_t *)malloc(L1_SIZE * sizeof(uint64_t));

        fill_buffer(target_buffer, TARGET_SIZE);
        fill_buffer(eviction_buffer, L1_SIZE);

        tmp = target_buffer[0];

        for (int i=0; i<SAMPLES*sec; i++){
            evict_from_Lx(eviction_buffer, L1_SIZE, 6);
            // printf("%ld\n", measure_one_block_access_time((uint64_t)target_buffer));
        };
        
        free((uint64_t *)eviction_buffer);
        free((uint64_t *)target_buffer);
    }
    else {
        sleep(sec);
    }

    printf("the bit has been sent!\n");

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


int getInputAfterDelay() {
    // Get the start time
    time_t startTime = time(NULL);

    // Collect an integer input from the user
    int userInput;
    printf("Enter an integer: ");
    scanf("%d", &userInput);

    // Calculate the end time by adding 5 seconds to the start time
    time_t endTime = startTime + 5;

    // Wait until the end time is reached
    while (time(NULL) < endTime) {
        // Waiting...
    }

    // Return the user input
    return userInput;
}