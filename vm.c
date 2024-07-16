#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vm.h"

// 'regs' is the array of registers i will have 4 registers.
__uint8_t regs[NUM_REGS];

// 'prog' is a list of instructions.
__uint8_t prog[] = {0};

// The program counter.
int pc = 0;

// Fetches the next instruction and increments the program counter.
__uint8_t fetch_instr() {
    return prog[pc++];
}

// Dynamically allocates memory for a decoded instruction.
void* allocate_decoded_instruction() {
    struct d_instr* d = malloc(sizeof(struct d_instr));
    assert(d != NULL);
    return d;
}

// Print an 8bit instruction
void print_8bit_instr(__uint8_t instr) {
    for (int i = 7; i >= 0; i--) {
        if (i == 3) {
            printf(" ");
        }
        printf("%d", (instr >> i) & 1);
    }
    printf("\n");
}

// Assume we have 8 bits 0000 0000
// The first 2 are the upcode or instrNum
// the second 2 are the r1
// the third 2 are the r2 and the last 2 are imm.
struct d_instr* decode(__uint8_t instr) {
    struct d_instr* de = allocate_decoded_instruction();
    de->upcode   = (instr >> 6);
    de->r1       = (instr >> 4) & 0x3;
    de->r2       = (instr >> 2) & 0x3;
    de->rst2     = (instr & 0x3);
    return de;
}


int main() {
    struct d_instr* d = decode(0xFF);
    free(d);
    return 0;
}