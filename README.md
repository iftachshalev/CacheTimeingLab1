# prime+probe example
### compile and execute:
  * compile with: gcc -O0 main.c -o main or use the makefile
  * run on core 2+ with: taskset -c 4 ./main or use the makefile
  * for more accurate/better results you might want to applay those changes:
    * disable hyper-threading
    * cancel c-state, sleep
    * set all CPUs to performance (maximum clock speed)
