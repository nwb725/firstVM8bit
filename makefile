CFLAGS=-Wall -Wextra -pedantic -std=c11

all: vm

vm: vm.o memory.o map_instructions.o map_helpers.o
	gcc vm.o memory.o map_instructions.o map_helpers.o -o vm $(CFLAGS) -lm

vm.o: vm.c
	gcc -c vm.c -o vm.o $(CFLAGS)

memory.o: memory.c
	gcc -c memory.c -o memory.o $(CFLAGS)

map_instructions.o: map_instructions.c
	gcc -c map_instructions.c -o map_instructions.o $(CFLAGS)

map_helpers.o: map_helpers.c
	gcc -c map_helpers.c -o map_helpers.o $(CFLAGS)

clean:
	rm -f *.o vm
