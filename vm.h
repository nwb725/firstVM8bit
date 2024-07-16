#ifndef VM_H

// r1 to r4 are the 4 general purpose registers, and r0 is zero.
#define NUM_REGS 5

// A struct for a decoded instruction.
struct d_instr {
    int upcode;
    int r1;
    int r2;
    int rst2;
};


#endif // VM_H