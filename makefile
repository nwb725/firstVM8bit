CFLAGS=-Wall -Wextra -pedantic -std=c11

all: vm

vm: vm.o memory.o
	gcc vm.o memory.o -o vm $(CFLAGS)

vm.o: vm.c
	gcc -c vm.c -o vm.o $(CFLAGS)

memory.o: memory.c
	gcc -c memory.c -o memory.o $(CFLAGS)

clean:
	rm -f *.o vm
