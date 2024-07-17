#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map_helpers.h"

struct instr_args* get_upcodes(struct instr_args* iargs) {
    char* instr = iargs->name;

    if (strcmp(instr, "LDI") == 0) {
        iargs->upcodes_4b = "0000";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "LD") == 0) {
        iargs->upcodes_4b = "0001";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "ST") == 0) {
        iargs->upcodes_4b = "0010";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "MOV") == 0) {
        iargs->upcodes_4b = "0011";
        iargs->num_args = 2;
        return iargs;
    }

    if (strcmp(instr, "ADD") == 0) {
        iargs->upcodes_4b = "0100";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "SUB") == 0) {
        iargs->upcodes_4b = "0101";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "MUL") == 0) {
        iargs->upcodes_4b = "0110";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "ADDI") == 0) {
        iargs->upcodes_4b = "0111";
        iargs->num_args = 2;
        return iargs;
    }

    if (strcmp(instr, "AND") == 0) {
        iargs->upcodes_4b = "1000";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "OR") == 0) {
        iargs->upcodes_4b = "1001";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "XOR") == 0) {
        iargs->upcodes_4b = "1010";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "NOT") == 0) {
        iargs->upcodes_4b = "1011";
        iargs->num_args = 2;
        return iargs;
    }

    if (strcmp(instr, "JMP") == 0) {
        iargs->upcodes_4b = "1100";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "JMPZ") == 0) {
        iargs->upcodes_4b = "1101";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "JMPNZ") == 0) {
        iargs->upcodes_4b = "1110";
        iargs->num_args = 2;
        return iargs;
    }
    if (strcmp(instr, "HLT") == 0) {
        iargs->upcodes_4b = "1110";
        iargs->num_args = 0;
        return iargs;
    }
    printf("Instruction name does not exist and didnt get matched: %s", instr);
    exit(EXIT_FAILURE);
}

char* get_regs(char* reg) {
    if (strcmp(reg, "r0") == 0) {
        return "00";
    } else if (strcmp(reg, "r1") == 0) {
        return "01";
    } else if (strcmp(reg, "r2") == 0) {
        return "10";
    } else if (strcmp(reg, "r3") == 0) {
        return "11";
    } else {
        printf("Unknown register: %s\n", reg);
        exit(EXIT_FAILURE);
    }
}