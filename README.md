<h1>prime+probe example:</h1>

  * compile with: gcc -O0 main.c -o main or use the makefile</h4>
run on core 2+ with: taskset -c 4 ./main or use the makefile</h4>
<h4>  - for more accurate/better results you might want to applay those changes:</h4>
<h5>  <t> * disable hyper-threading</h5>
<h5>  <t> * cancel c-state, sleep</h5>
<h5>  <t> * set all CPUs to performance (maximum clock speed)</h5>
