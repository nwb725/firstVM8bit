#ifndef MAP_INSTRUCTIONS_H
#define MAP_INSTRUCTIONS_H

#define PROGRAM_PATH "../firstVM8bit/program.txt"

struct instr_to_8bit {
    char name;
    char r1;
    char rst2;
    char full_8bit_instr;
};

void print_instr_split();
void read_program_file();

#endif // MEMORY_H