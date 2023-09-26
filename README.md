<h1>prime+probe example:</h1>
<h2>  - compile with: gcc -O0 main.c -o main or use the makefile</h2>
<h2>  - run on core 2+ with: taskset -c 4 ./main or use the makefile</h2>
<h2>  - for more accurate/better results you might want to applay those changes:</h2>
<h3>      * disable hyper-threading</h3>
<h3>      * cancel c-state, sleep</h3>
<h3>      * set all CPUs to performance (maximum clock speed)</h3>
