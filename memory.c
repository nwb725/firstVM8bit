#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "memory.h"

// Memory for the machine.
// I've chosen to only have 256 bytes of memory for simplicity.
// The first 64 bytes are for general purpose use.
// The last 192 bytes are reserved for the instructions (the program).
uint8_t memory[MEMORY_SIZE];


/// @brief Initializes memory, Sets all values in memory to 0.
void init_memory() {
    for (int i=0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
}

/// @brief Fetches the instruction in memory[pc].
/// @param pc The program counter.
/// @return Returns an instruction.
uint8_t fetch_instr(int pc) {
    if (pc > MEMORY_SIZE) {
        printf("%s", "Program counter exceded 254 which is the max number of instructions, an error has ocurred.");
        return 1;
    }
    return memory[pc];
}

/// @brief Prints all values in memory as base 16 hex.
void print_memory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%02x ", memory[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

/// @brief Writes a value to memory.
/// @param address The address to write to.
/// @param value The value to write.
void write_memory(uint8_t address, uint8_t value) {
    memory[address] = value;
}

/// @brief Reads a value from memory.
/// @param address The address to read from.
/// @return Returns memory[address].
uint8_t read_memory(uint8_t address) {
    return memory[address];
}
