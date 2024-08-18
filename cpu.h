#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// Using multibyte instructions, we have 16 registers.
#define NUM_REGS 16
#define RUNNING 0
#define HALT 1
#define PROG_START_ADDR 64

// A struct for a decoded instruction.
struct d_instr {
    uint8_t upcode;
    uint8_t upcode2;
    uint8_t r1;
    uint8_t rst2;
};

enum Register {
    R0 = 0, // Always 0
    PC,     // Holds the program counter.
    LR,     // Link return register.
    SP,     // Points to the top of the stack
    ACC,    // Accumulator, used for arithmetic.
    t1,     // Temporary register 1
    t2,     // Temporary register 2
    t3      // Temporary register 3
};

void run_program(uint8_t);
void reset_regs();
void init_regs();
void print_regs();


#endif // VM_H