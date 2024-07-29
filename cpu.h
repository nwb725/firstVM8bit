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



#endif // VM_H