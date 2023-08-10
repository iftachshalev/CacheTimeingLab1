include ../cpu.mk

all: main

run:
	./main.exe

run-reference: reference
	@taskset -c $(SENDER_CPU) ./reference

main: main.c Makefile
	@gcc main.c -o main.exe

.PHONY: clean

clean:
	rm -f main.exe
