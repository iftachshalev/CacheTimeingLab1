#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <unistd.h>

#define TARGET_SIZE 8
#define L1_SIZE 256 * 1024 * 4.5

int getInputAfterDelay();
 

int main (int ac, char **av) {

    int sec = 2;

    printf("<<<you have 5 seconds to enter an input>>>\n");
    int bit = getInputAfterDelay();
    printf("sending bit...\n");

    if (bit == 1) {
        volatile char tmp;
        srand(time(NULL));

        volatile uint64_t *target_buffer = (volatile uint64_t *)malloc(TARGET_SIZE * sizeof(uint64_t));
        volatile uint64_t *eviction_buffer = (volatile uint64_t *)malloc(L1_SIZE * sizeof(uint64_t));

        fill_buffer(target_buffer, TARGET_SIZE);
        fill_buffer(eviction_buffer, L1_SIZE);

        tmp = target_buffer[0];

        for (int i=0; i<SAMPLES*sec; i++){evict_from_Lx(eviction_buffer, L1_SIZE, 6);}
        
        free((uint64_t *)eviction_buffer);
        free((uint64_t *)target_buffer);
    }
    else {
        sleep(sec);
    }

    printf("the bit has been sent!\n");

    return 0;
}


int getInputAfterDelay() {
    // Get the start time
    time_t startTime = time(NULL);

    // Collect an integer input from the user
    int userInput;
    printf("Enter a bit: ");
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