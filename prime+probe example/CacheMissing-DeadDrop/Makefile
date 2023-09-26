.PHONY: all run clean

all: receiver sender

run:
	gnome-terminal -- bash -c 'taskset -c 4 ./receiver; exec bash' & \
	gnome-terminal -- bash -c 'taskset -c 4 ./sender; exec bash' &

receiver: receiver.c Makefile
	gcc -g -O0 receiver.c -o receiver

sender: sender.c Makefile
	gcc -g -O0 sender.c -o sender

clean:
	rm -f sender
	rm -f receiver
	rm -f *.o