#include"util.h"
#include<windows.h>
#include <stdio.h>
#include <time.h>
#define L1_SIZE 47652 // pc
#define L2_SIZE 400000 // pc
#define THRESHOLD 100

void evict_to_Lx(uint64_t *eviction_buffer, size_t size);

int main(int argc, char **argv)
{
	
	printf("Please press enter.\n");
	char text_buf[2];
	fgets(text_buf, sizeof(text_buf), stdin);
	printf("Receiver now listening.\n");

	volatile char tmp;
	uint64_t *target_buffer = (uint64_t *)malloc(8 * sizeof(uint64_t));
	uint64_t *eviction_buffer = (uint64_t *)malloc(L1_SIZE * sizeof(uint64_t));
	// clflush((uint64_t)&target_buffer[0]);
	for (int i = 0; i < 8; i++) {
		tmp = target_buffer[i];
	}
	
	evict_to_Lx(eviction_buffer, L1_SIZE);
	evict_to_Lx(eviction_buffer, L1_SIZE);
	evict_to_Lx(eviction_buffer, L1_SIZE);
	evict_to_Lx(eviction_buffer, L1_SIZE);


	Sleep(5000); // the sender evict all l2 if bit is 1 =============


	int latency = measure_one_block_access_time((uint64_t)target_buffer);
	printf("\n%d\n", latency);

	if (latency > THRESHOLD) {
		printf("the bit 1!\n");
	} else {
		printf("the bit is 0!\n");
	}

	free(target_buffer);
	free(eviction_buffer);

	return 0;
}


void evict_to_Lx(uint64_t *eviction_buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        uint64_t value = eviction_buffer[i];
    }
}
