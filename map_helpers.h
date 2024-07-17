#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

struct instr_args {
    char* name;
    char* upcodes_4b;
    int num_args;
};

struct instr_args* get_upcodes(struct instr_args* iargs);
char* get_regs(char* instr);

#endif // MEMORY_H
