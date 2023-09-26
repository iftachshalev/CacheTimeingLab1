<h1>prime+probe example:</h1>
<h3>  - compile with: gcc -O0 main.c -o main or use the makefile</h3>
<h3>  - run on core 2+ with: taskset -c 4 ./main or use the makefile</h3>
<h3>  - for more accurate/better results you might want to applay those changes:</h3>
<h4>      * disable hyper-threading</h4>
<h4>      * cancel c-state, sleep</h4>
<h4>      * set all CPUs to performance (maximum clock speed)</h4>
