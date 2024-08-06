#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H


struct instr_args {
    // Instruction name.
    char* name;
    // 4bits of upcode.
    char* upcodes_4b;
    // Number of arguments.
    int num_args;
    // 0 if it does not use immidiate and 1 if it does.
    int has_imm;
    // 0 if it does not use a label and 1 if it does.
    int has_label;
};

void get_upcodes(struct instr_args* iargs);
char* get_regs(char* instr);

#endif // MEMORY_H
