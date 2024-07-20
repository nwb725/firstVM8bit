CFLAGS=-Wall -Wextra -pedantic -std=c11

all: vm

vm: cpu.o memory.o assembler.o assembler_utils.o
	gcc cpu.o memory.o assembler.o assembler_utils.o -o vm $(CFLAGS) -lm

cpu.o: cpu.c
	gcc -c cpu.c -o cpu.o $(CFLAGS)

memory.o: memory.c
	gcc -c memory.c -o memory.o $(CFLAGS)

assembler.o: assembler.c
	gcc -c assembler.c -o assembler.o $(CFLAGS)

assembler_utils.o: assembler_utils.c
	gcc -c assembler_utils.c -o assembler_utils.o $(CFLAGS)

clean:
	rm -f *.o vm
