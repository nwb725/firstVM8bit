#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// r1 to r4 are the 4 general purpose registers, and r0 is zero.
#define NUM_REGS 4
#define RUNNING 0
#define HALT 1

// A struct for a decoded instruction.
struct d_instr {
    uint8_t upcode;
    uint8_t upcode2;
    uint8_t r1;
    uint8_t rst2;
};


#endif // VM_H