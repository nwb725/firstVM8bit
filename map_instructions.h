#ifndef MAP_INSTRUCTIONS_H
#define MAP_INSTRUCTIONS_H

#define PROGRAM_PATH "../firstVM8bit/program.txt"
#define DEFAULT_REG_VAL "00"

struct instr_to_8bit {
    char* name;
    char* r1;
    char* rst2;
};


void print_instr_split();
void read_program_file();
uint8_t* get_program();

#endif // MEMORY_H