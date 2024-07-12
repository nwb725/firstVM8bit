CFLAGS=-Wall -Wextra -pedantic -std=c11

all: vm

vm: vm.c
	gcc vm.c -o vm $(CFLAGS)

clean: 
	rm -rf *.o vm