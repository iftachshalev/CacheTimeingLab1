# Prime+probe example
### Compile and execute:
  * compile with: `gcc -O0 prog_name.c -o prog_name` or use the makefile
  * run on core 2+ with: `taskset -c 4 ./prog_name` or use the makefile
  * for more accurate/better results you might want to applay those changes:
    * disable hyper-threading
    * cancel c-state, sleep
    * set all CPUs to performance (maximum clock speed). info [here](https://askubuntu.com/questions/20271/how-do-i-set-the-cpu-frequency-scaling-governor-for-all-cores-at-once)
### Cache-timing:
