#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

#define PROGRAM_PATH "../firstVM8bit/program.txt"
#define DEFAULT_REG_VAL "0000"
#define MAX_INSTRUCTIONS (MEMORY_SIZE - PROG_START_ADDR) / 2

struct instr_to_8bit {
    // 4bits of upcode.
    char* name;
    // 2bits for r1.
    char* r1;
    // 2bits for rst2.
    char* rst2;
};


void print_instr_split();
void read_program_file();
void get_program();

#endif