#include"util.h"
#include<windows.h>
#define SAMPLES 100
#define BUFFERS 10

#define L1_SIZE 47652 // pc
#define L2_SIZE 3293216 // pc

void evict_to_Lx(uint64_t *eviction_buffer, size_t size);
void print_results(uint64_t* l2_latency);
void load_l2(uint64_t **array);
int latency_check(uint64_t **array);
int compare(const void *p1, const void *p2);

int main(int argc, char **argv)
{
	
	printf("Please press enter.\n");
	char text_buf[2];
	fgets(text_buf, sizeof(text_buf), stdin);
	printf("Receiver now listening.\n");


	uint64_t **array = (uint64_t **)malloc(BUFFERS * sizeof(uint64_t *));
	load_l2(array);

	uint64_t *evict_l2 = (uint64_t *)malloc(L2_SIZE * sizeof(uint64_t));
	// evict_to_Lx(evict_l2, L2_SIZE);
	// evict_to_Lx(evict_l2, L2_SIZE);
	// evict_to_Lx(evict_l2, L2_SIZE);
	// evict_to_Lx(evict_l2, L2_SIZE);
	printf("\n\n%d", latency_check(array));

	

	for (int i = 0; i < BUFFERS; i++) {
        free(array[i]);
    }
	free(array);

	return 0;
}

void load_l2(uint64_t **array) {
	volatile char tmp;
	uint64_t *eviction_buffer = (uint64_t *)malloc(L1_SIZE * sizeof(uint64_t));

	for (int i = 0; i < BUFFERS; i++) {
		uint64_t *target_buffer = array[i];
		uint64_t l2_latency[SAMPLES] = {0};

		for (int i=0; i<SAMPLES; i++){
			tmp = target_buffer[0];
		}
		for (int i = 0; i < SAMPLES; i++) {
			evict_to_Lx(eviction_buffer, L1_SIZE);
			evict_to_Lx(eviction_buffer, L1_SIZE);
			evict_to_Lx(eviction_buffer, L1_SIZE);
			evict_to_Lx(eviction_buffer, L1_SIZE);
			// l2_latency[i] = measure_one_block_access_time((uint64_t)target_buffer);
		}
		// print_results(l2_latency);
	}
	free(eviction_buffer);

}

int latency_check(uint64_t **array) {
	// get array
	uint64_t l2_latency[BUFFERS] = {0};
	for (int i = 0; i < BUFFERS; i++) {
		l2_latency[i] = measure_one_block_access_time((uint64_t)array[i]);
		printf("\n%d\n", l2_latency[i]);
	}

	// threshhold
	// qsort(l2_latency, BUFFERS, sizeof(uint64_t), compare);
	// printf("\n%d, %d\n", l2_latency[0], l2_latency[9]);
	// if (l2_latency[0] < 100) {
	// 	return 1;
	// }
	return 0;
}


int compare(const void *p1, const void *p2) {
    uint64_t u1 = *(uint64_t *)p1;
    uint64_t u2 = *(uint64_t *)p2;

    return (int)u1 - (int)u2;
}


void evict_to_Lx(uint64_t *eviction_buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        uint64_t value = eviction_buffer[i];
		if (value == 1) {
			printf("%lu", value);
		}
    }
}


void print_results(uint64_t* l2_latency){
	qsort(l2_latency, SAMPLES, sizeof(uint64_t), compare);
	printf("Minimum      : %5ld\n", l2_latency[0]);

    printf("Bottom decile: %5ld\n", l2_latency[SAMPLES/10]);

    printf("Median       : %5ld\n", l2_latency[SAMPLES/2]);

    printf("Top decile   : %5ld\n", l2_latency[(SAMPLES*9)/10]);

    printf("Maximum      : %5ld\n", l2_latency[SAMPLES-1]);
};
