#include <stdio.h>
#include <stdlib.h>

#define NUM_REGS 4

// 'regs' is the array of registers i will have 4 registers.
__uint8_t regs[NUM_REGS];

// 'prog' is a list of instructions.
__uint8_t prog[] = {0};

// The program counter.
int pc = 0;

struct d_instr {
    int instrNum;
    int r1;
    int r2;
    int imm;
};

__uint8_t fetch_instr() {
    return prog[pc++];
}


// Assume we have 8 bits 0000 0000
// The first 2 are the upcode or instrNum
// the second 2 are the r1
// the third 2 are the r2 and the last 2 are imm.
struct d_instr* decode(__uint8_t instr) {
    struct d_instr* de = malloc(sizeof(struct d_instr));
    de->instrNum = (instr >> 6);
    de->r1       = (instr >> 4) & 0x3;
    de->r2       = (instr >> 2) & 0x3;
    de->imm      = (instr & 0x3);
    return de;
    // Needs to set the registers to the correct values.
}


int main() {
    struct d_instr* d = decode(0xFF);
    printf("%d\n", d->r2);
    free(d);
    return 0;
}