#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "vm.h"
#include "memory.h"

// 'regs' is the array of registers i will have 5 registers.
uint8_t regs[NUM_REGS];

// 'prog' is a list of instructions.
uint8_t prog[] = {0};

// The program counter.
int pc = 0;

// The running flag, is only set to 1 if HLT is executed.
int running = RUNNING;

// A temporary variable.
int temp;

// Fetches the next instruction and increments the program counter.
uint8_t fetch_instr() {
    if (pc == 254) {
        printf("%s", "Last instruction to execute, instruction 254.");
    }
    if (pc > 254) {
        printf("%s", "Program counter exceded 254 which is the max number of instructions, an error has ocurred.");
        return 1;
    }
    return prog[pc++];
}

// Dynamically allocates memory for a decoded instruction.
void* allocate_decoded_instruction() {
    struct d_instr* d = malloc(sizeof(struct d_instr));
    assert(d != NULL);
    return d;
}

// Print an 8bit instruction
void print_8bit_instr(uint8_t instr) {
    for (int i = 7; i >= 0; i--) {
        if (i == 3) {
            printf(" ");
        }
        printf("%d", (instr >> i) & 1);
    }
    printf("\n");
}

// Assume we have 8 bits 0000 0000
// The first 2 are the upcode
// the second 2 are the second upcode
// the third 2 are the r1 
// and the last 2 are r2/imm/addr.
struct d_instr* decode(uint8_t instr) {
    struct d_instr* de = allocate_decoded_instruction();
    de->upcode   = (instr >> 6);
    de->upcode2  = (instr >> 4) & 0x3;
    de->r1       = (instr >> 2) & 0x3;
    de->rst2     = (instr & 0x3);
    return de;
}


void execute_instructions() {
    uint8_t curr_instr = fetch_instr();
    struct d_instr* d_curr_instr = decode(curr_instr);
    int r1 = d_curr_instr->r1;
    int rst2 = d_curr_instr->rst2;


    switch (d_curr_instr->upcode) {
    // Data movement - upcode '00'
    case 0x0:
        switch (d_curr_instr->upcode2) {
        // LDI - Load immidiate rst2 into r1.
        case 0x0:
            regs[r1] = rst2;
            break;
        // LD - Load value from addr[rst2] into r1
        case 0x1:
            regs[r1] = read_memory(rst2);
            break;
        // ST - Store value from r1 into addr in rst2
        case 0x2:
            write_memory(rst2, r1);
            break;
        // MOV - Moves value from rst2 into r1.
        case 0x3:
            regs[r1] = regs[rst2];
            break;
        default:
            break;
        }
        break;
    // Arithmetic - upcode '01'
    case 0x1:
        switch (d_curr_instr->upcode2) {
        // ADD - Add values in r1 with rst2, and stores in r1.
        case 0x0:
            regs[r1] += regs[rst2];
            break;
        // SUB - Subtract values in r1 with rst2, and stores in r1.
        case 0x1:
            regs[r1] -= regs[rst2];
            break;
        // MUL - Multiply values in r1 with rst2, and stores in r1.
        case 0x2:
            regs[r1] *= regs[rst2];
            break;
        // ADDI - Add value in r1 with immidiate value in rst2, and stores in r1. 
        case 0x3:
            regs[r1] += rst2;
            break;
        default:
            break;
        }
        break;
    // Logical - upcode '10'  
    case 0x2:
        switch (d_curr_instr->upcode2) {
        // AND - bitwise ANDs values in register r1 and rst2 and stores in r1.
        case 0x0:
            regs[r1] &= regs[rst2];
            break;
        // OR - bitwise ORs values in register r1 and rst2 and stores in r1.
        case 0x1:
            regs[r1] |= regs[rst2];
            break;
        // XOR - bitwise XORs values in register r1 and rst2 and stores in r1.
        case 0x2:
            regs[r1] ^= regs[rst2];
            break;
        // NOT - bitwise NOT value in r1 and stores in rst2. 
        case 0x3:
            regs[rst2] = ~regs[r1];
            break;
        default:
            break;
        }
        break;  
    // Control flow - upcode '11'
    case 0x3:
        switch (d_curr_instr->upcode2) {
        // JMP - Jumps to address r1 + rst2 lets say: xxxx 0110, then 'JMP 6'
        case 0x0:
            // Keeps only the last 4 bits for jumping addr.
            temp = (curr_instr & 0xF);
            pc = temp;
            break;
        // JMPZ - Jumps to addr rst2 only if value in r1 is zero.
        case 0x1:
            if (regs[r1] == 0) {
                printf("JMPZ - Jumping to: %d\n", regs[rst2]);
                pc = regs[rst2];
            }
            break;
        // JMPNZ - Jumps to addr rst2 only if value in r1 is NOT zero.
        case 0x2:
            if (regs[r1] != 0) {
                printf("JMPNZ - Jumping to: %d\n", regs[rst2]);
                pc = regs[rst2];
            }
            break;
        // HLT - Stops execution. 
        case 0x3:
            printf("HLT - Execution is halted.\n");
            running = HALT;
            break;
        default:
            break;
        }
        break; 


    default:
        printf("Default case for 'upcode', should never land here.");
        break;
    }
    free(d_curr_instr);
}

void run_program() {
    while (running == RUNNING) {
        execute_instructions();
    }
}

int main(int argc, char **argv) {
    run_program();
    return 0;
}