#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

#define PROGRAM_PATH "../firstVM8bit/program.txt"
#define DEFAULT_REG_VAL "00"
#define OUTPUT_FILE "program_assemble.txt"
#define MAX_INSTRUCTIONS 192

struct instr_to_8bit {
    char* name;
    char* r1;
    char* rst2;
};


void print_instr_split();
void read_program_file();
void get_program();

#endif