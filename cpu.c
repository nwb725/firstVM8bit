#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "cpu.h"
#include "memory.h"
#include "assembler.h"
#include "symtab.h"


// 'regs' is the array of registers i will have 15 registers.
// r0 - Is always 0.
// TEMPORARY: r1 .. r14 - General purpose registers.
uint8_t regs[NUM_REGS];

// The program counter, starts at 64 always.
// The last 192 bytes in memory are reserved for instructions.
int pc;

// The running flag, is only set to HALT if HLT is executed.
// Where the machine then halts.
int running = RUNNING;

// A temporary variable...
int temp;

/// @brief Initializes all register values to 0.
void init_regs() {
    for (int i = 0; i<NUM_REGS; i++) {
        regs[i] = 0;
    }
}

/// @brief Resets registers to initial value.
void reset_regs() {
    init_regs();
}

/// @brief Prints the values in each register
void print_regs() {
    for (int i = 0; i <NUM_REGS; i++) {
        printf("REG[%d] = %d\n", i, regs[i]);
    }
}

/// @brief Dynamically allocates memory for a decoded instruction.
/// @return Returns a pointer the the decoded instruction.
void* allocate_decoded_instruction() {
    struct d_instr* d = malloc(sizeof(struct d_instr));
    assert(d != NULL);
    return d;
}


/// @brief Print an 8bit instruction. 
/// Takes a uint8_t and prints 8bits -> '0000 0000'.
/// @param instr The instruction to print.
void print_8bit_instr(uint8_t instr) {
    for (int i = 7; i >= 0; i--) {
        if (i == 3) {
            printf(" ");
        }
        printf("%d", (instr >> i) & 1);
    }
    printf("\n");
}


/// @brief Decodes a multibyte instruction.
/// Assume we have the first 8 bits: first 4 bits are first and second upcode,
/// the next 4 bits are for the first register. It then fetches the next instruction,
/// Where either the 4 least significant bits are a register or an 8bit immidiate.
struct d_instr* multibyte_decode(uint8_t instr) {
    struct d_instr* de = allocate_decoded_instruction();
    de->upcode   = (instr >> 6);
    de->upcode2  = (instr >> 4) & 0x3;
    de->r1       = (instr & 0xF);
    de->rst2     = fetch_instr(++pc);
    return de;
}

/// @brief The function for executing instructions.
/// It fetches the next instruction, matches the upcode,
/// and executes it. Then updates the program counter.
void execute_instructions() {
    uint8_t curr_instr = fetch_instr(pc);
    struct d_instr* d_curr_instr = multibyte_decode(curr_instr);
    int r1 = d_curr_instr->r1;
    int rst2 = d_curr_instr->rst2;

    switch (d_curr_instr->upcode) {
    // Data movement - upcode '00'
    case 0x0:
        switch (d_curr_instr->upcode2) {
        // LDI - Load immidiate rst2 into r1.
        // RET - Pops from the return stack.
        case 0x0:
            if (r1 == 0) {
                uint8_t addr = stack_pop();
                printf("RET <%d>\n", addr);
                pc = addr - 1;
                break;
            }
            printf("LDI r%d %d\n", r1, rst2);
            regs[r1] = rst2;
            break;
        // LD - Load value from addr[rst2] into r1
        case 0x1:
            printf("LD r%d r%d\n", r1, rst2);
            regs[r1] = read_memory(rst2);
            break;
        // ST - Store value from r1 into addr in rst2
        case 0x2:
            printf("ST r%d r%d\n", r1, rst2);
            write_memory(rst2, r1);
            break;
        // MOV - Moves value from rst2 into r1.
        case 0x3:
            printf("MOV r%d r%d\n", r1, rst2);
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
            printf("ADD r%d r%d\n", r1, rst2);
            regs[r1] += regs[rst2];
            break;
        // SUB - Subtract values in r1 with rst2, and stores in r1.
        case 0x1:
            printf("SUB r%d r%d\n", r1, rst2);
            regs[r1] -= regs[rst2];
            break;
        // MUL - Multiply values in r1 with rst2, and stores in r1.
        case 0x2:
            printf("MUL r%d r%d\n", r1, rst2);
            regs[r1] *= regs[rst2];
            break;
        // ADDI - Add value in r1 with immidiate value in rst2, and stores in r1. 
        case 0x3:
            printf("ADDI r%d %d\n", r1, rst2);
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
            printf("AND r%d r%d\n", r1, rst2);
            regs[r1] &= regs[rst2];
            break;
        // OR - bitwise ORs values in register r1 and rst2 and stores in r1.
        case 0x1:
            printf("OR r%d r%d\n", r1, rst2);
            regs[r1] |= regs[rst2];
            break;
        // XOR - bitwise XORs values in register r1 and rst2 and stores in r1.
        case 0x2:
            printf("XOR r%d r%d\n", r1, rst2);
            regs[r1] ^= regs[rst2];
            break;
        // NOT - bitwise NOT value in rst2 and stores in r1. 
        case 0x3:
            printf("NOT r%d r%d\n", r1, rst2);
            regs[r1] = ~regs[rst2];
            break;
        default:
            break;
        }
        break;  
    // Control flow - upcode '11'
    // Subtracting one from jumps since pc gets updated anyway.
    case 0x3:
        switch (d_curr_instr->upcode2) {
        // JMP - Jumps address stored in rst2.
        // rst2 is a label, that is mapped to an address in the assembler.
        // Might need to rethink the logic here...
        case 0x0:
            printf("JMP %d\n", rst2);
            // Keeps only the last 4 bits for jumping addr.
            pc = rst2 - 1;
            break;
        // JMPZ - Jumps to addr rst2 only if value in r1 is zero.
        case 0x1:
            printf("JMPZ r%dr%d", r1, rst2);
            if (regs[r1] == 0) {
                pc = rst2;
            }
            break;
        // JMPNZ - Jumps to addr rst2 only if value in r1 is NOT zero.
        case 0x2:
            printf("JMPNZ r%d %d\n", r1, rst2);
            if (regs[r1] != 0) {
                pc = rst2;
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
        printf("Default case for 'upcode', should never land here.\n");
        printf("The current last instruction was: %d", curr_instr);
        break;
    }
    free(d_curr_instr);
    pc++;
}

/// @brief Runs the program, only stops when the HALT flag is set.
/// First it assembles the program.txt file
/// Then it writes it to memory
/// The registers are then initialized to 0.
void run_program(uint8_t entry) {
    pc = entry;
    while (running != HALT) {
        execute_instructions();
    }
    stack_destroy();
}
