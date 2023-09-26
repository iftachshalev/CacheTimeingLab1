all: main

run:
	@taskset -c 4 ./main

main: main.c Makefile
	@gcc -g -O0 main.c -o main

.PHONY: clean

clean:
	rm -f main
