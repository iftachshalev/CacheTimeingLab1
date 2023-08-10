
#include"util.h"
#include <string.h>
#include<windows.h>
// TODO: define your own buffer size
#define BUFF_SIZE (1<<21)
#define L1_SIZE 47652 // times 1.5
#define L2_SIZE 400000 // times 1.5


void encoderSB(char *bit);
void evict_to_Lx(uint64_t *eviction_buffer, size_t size);


int main(int argc, char **argv)
{

  printf("Please type a message.\n");
  char text_buf[128];
  fgets(text_buf, sizeof(text_buf), stdin);
  char *bin_inp = string_to_binary(text_buf);
  printf("%s\n", bin_inp);
  bin_inp = "1";
  encoderSB(bin_inp);

  printf("Sender finished.\n");
  return 0;
}


void encoderSB(char *bit) {

  volatile char tmp;
  printf("encoding for: %s\n", bit);

  if (strcmp(bit, "1") == 0) {
    uint64_t *target_buffer = (uint64_t *)malloc(L2_SIZE * sizeof(uint64_t));
    tmp = target_buffer[0];
    // printf("%d\n", measure_one_block_access_time((uint64_t)target_buffer));
    free(target_buffer);
  } else {
    printf("the bit is 0");
  }

}


void evict_to_Lx(uint64_t *eviction_buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        uint64_t value = eviction_buffer[i];
    }
}

