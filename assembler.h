#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

#define PROGRAM_PATH "../firstVM8bit/program.txt"
#define DEFAULT_REG_VAL "0000"
#define MAX_INSTRUCTIONS (MEMORY_SIZE - PROG_START_ADDR) / 2
#define PROGRAM_ENTRY_POINT "MAIN"
#define LABEL_FLAG NULL
struct instr_to_8bit {
    // 4bits of upcode.
    char* name;
    // 4bits for r1.
    char* r1;
    // 4bits for rst2 OR up to 8 bit imm.
    char* rst2;
};

void print_instr_split();
void read_program_file(const char* fname);
uint8_t get_program(const char* fp);

#endif