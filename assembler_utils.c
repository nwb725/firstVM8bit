#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assembler_utils.h"

/// @brief Gets called in the assembler, maps the name of an instruction
/// to a given upcode 1 and 2 - and the number of arguments for that instruction.
/// IMPORTANT: Instructions that use immidiates such as LDI
/// Will be set to have 1 argument, and will be handled in assembler.
/// (LDI and ADDI).
/// @param iargs A pointer to the current instruction, contains only name.
void get_upcodes(struct instr_args* iargs) {
    char* instr = iargs->name;

    if (strcmp(instr, "LDI") == 0) {
        iargs->upcodes_4b = "0000";
        iargs->num_args = 1;
        iargs->has_imm = 1;
    }
    if (strcmp(instr, "LD") == 0) {
        iargs->upcodes_4b = "0001";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "ST") == 0) {
        iargs->upcodes_4b = "0010";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "MOV") == 0) {
        iargs->upcodes_4b = "0011";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "ADD") == 0) {
        iargs->upcodes_4b = "0100";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "SUB") == 0) {
        iargs->upcodes_4b = "0101";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "MUL") == 0) {
        iargs->upcodes_4b = "0110";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "ADDI") == 0) {
        iargs->upcodes_4b = "0111";
        iargs->num_args = 1;
        iargs->has_imm = 1;
    }

    if (strcmp(instr, "AND") == 0) {
        iargs->upcodes_4b = "1000";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "OR") == 0) {
        iargs->upcodes_4b = "1001";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "XOR") == 0) {
        iargs->upcodes_4b = "1010";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "NOT") == 0) {
        iargs->upcodes_4b = "1011";
        iargs->num_args = 2;
    }

    if (strcmp(instr, "JMP") == 0) {
        iargs->upcodes_4b = "1100";
        iargs->num_args = 1;
    }
    if (strcmp(instr, "JMPZ") == 0) {
        iargs->upcodes_4b = "1101";
        iargs->num_args = 1;
        iargs->has_imm = 1;
    }
    if (strcmp(instr, "JMPNZ") == 0) {
        iargs->upcodes_4b = "1110";
        iargs->num_args = 1;
        iargs->has_imm = 1;
    }
    if (strcmp(instr, "HLT") == 0) {
        iargs->upcodes_4b = "1111";
        iargs->num_args = 0;
    }
    // Needs to be handled and error if the instruction name does not exist.
}

/// @brief Maps the register name to a given hex value.
/// @param reg The register name to map. 
/// @return Returns a hex value that matches the register name.
char* get_regs(char* reg) {
    if (strcmp(reg, "r0") == 0) {
        return "0000";
    } 
    if (strcmp(reg, "r1") == 0) {
        return "0001";
    } 
    if (strcmp(reg, "r2") == 0) {
        return "0010";
    } 
    if (strcmp(reg, "r3") == 0) {
        return "0011";
    }
    if (strcmp(reg, "r4") == 0) {
        return "0100";
    } 
    if (strcmp(reg, "r5") == 0) {
        return "0101";
    } 
    if (strcmp(reg, "r6") == 0) {
        return "0110";
    } 
    if (strcmp(reg, "r7") == 0) {
        return "0111";
    }
    if (strcmp(reg, "r8") == 0) {
        return "1000";
    } 
    if (strcmp(reg, "r9") == 0) {
        return "1001";
    } 
    if (strcmp(reg, "r10") == 0) {
        return "1010";
    } 
    if (strcmp(reg, "r11") == 0) {
        return "1011";
    }
    if (strcmp(reg, "r12") == 0) {
        return "1100";
    } 
    if (strcmp(reg, "r13") == 0) {
        return "1101";
    } 
    if (strcmp(reg, "r14") == 0) {
        return "1110";
    } 
    if (strcmp(reg, "r15") == 0) {
        return "1111";
    } else {
        printf("Error in mapping register. Got: %s\n", reg);
        exit(EXIT_FAILURE);
    }
}