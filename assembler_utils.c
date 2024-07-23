#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assembler_utils.h"

/// @brief Gets called in the assembler, maps the name of an instruction
/// to a given upcode 1 and 2 - and the number of arguments for that instruction.
/// @param iargs A pointer to the current instruction, contains only name.
void get_upcodes(struct instr_args* iargs) {
    char* instr = iargs->name;

    if (strcmp(instr, "LDI") == 0) {
        iargs->upcodes_4b = "0000";
        iargs->num_args = 2;
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
        iargs->num_args = 2;
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
        iargs->num_args = 2;
    }
    if (strcmp(instr, "JMPZ") == 0) {
        iargs->upcodes_4b = "1101";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "JMPNZ") == 0) {
        iargs->upcodes_4b = "1110";
        iargs->num_args = 2;
    }
    if (strcmp(instr, "HLT") == 0) {
        iargs->upcodes_4b = "1111";
        iargs->num_args = 0;
    }
/*     else {
        printf("Instruction name does not exist and didnt get matched: %s\n", instr);
        exit(EXIT_FAILURE);   
    } */
}

/// @brief Maps the register name to a given hex value.
/// @param reg The register name to map. 
/// @return Returns a hex value that matches the register name.
char* get_regs(char* reg) {
    if (strcmp(reg, "r0") == 0) {
        return "00";
    } 
    if (strcmp(reg, "r1") == 0) {
        return "01";
    } 
    if (strcmp(reg, "r2") == 0) {
        return "10";
    } 
    if (strcmp(reg, "r3") == 0) {
        return "11";
    } else {
        return reg;
    }
}