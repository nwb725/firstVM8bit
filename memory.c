#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "memory.h"

uint8_t memory[MEMORY_SIZE];

// Initializes memory.
void init_memory() {
    for (int i=0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
}

uint8_t fetch_instr(int pc) {
    if (pc > MEMORY_SIZE) {
        printf("%s", "Program counter exceded 254 which is the max number of instructions, an error has ocurred.");
        return 1;
    }
    return memory[pc];
}


void print_memory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%02x ", memory[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Writes to memory
void write_memory(uint8_t address, uint8_t value) {
    memory[address] = value;
}

// Reads from memory
uint8_t read_memory(uint8_t address) {
    return memory[address];
}
