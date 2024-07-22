#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cpu.h"
#include "memory.h"
#include "assembler.h"
#include "assembler_utils.h"


/// @brief A buffer for the instructions that are read from program.txt.
char instrs[MAX_INSTRUCTIONS];

/// @brief This points to a list that holds all uint8_t values for all instructions.
uint8_t* p;

/// @brief Counts the number of instructions in a program.
/// @param fp The program file.
/// @return Returns the number of instructions.
int count_instructions(const char *fp) {
    FILE *file = fopen(fp, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int lines = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    // If the file is not empty and does not end with a newline, count the last line
    if (ch != '\n' && lines != 0) {
        lines++;
    }

    fclose(file);
    return lines;

}

/// @brief Reads the program into the buffer (instrs).
void read_program_file() {
    // Opens the file for reading
    FILE* prg_stream = fopen(PROGRAM_PATH, "r");
    if (prg_stream == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the file content into instrs buffer
    size_t read_bytes = fread(instrs, 1, sizeof(instrs) - 1, prg_stream);

    // Null-terminate the string
    instrs[read_bytes] = '\0';

    fclose(prg_stream);
}

/// @brief Takes a binary representation of an instruction and returns the integer value.
/// @param in The binary instruction to translate.
/// @return Returns an integer value representing the instruction.
uint8_t binary_to_uint_8b(struct instr_to_8bit* in) {

    // First part here is just copying an concatting the 2 bits for rst2 onto r1.
    size_t reg_length = strlen(in->r1) + strlen(in->rst2) + 1;
    size_t name_length = strlen(in->name) + 1;

    char* reg_combined = (char *)malloc(reg_length);
    if (reg_combined == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    strcpy(reg_combined, in->r1);
    strcat(reg_combined, in->rst2);

    // Now we loop over the string and see if it is 1 then +=i^2.
    uint8_t reg_val = 0;
    uint8_t name_val = 0;
    int inc = -1;

    // First name:
    for (int i = name_length-1; i > -1; i--) {
        if (in->name[i] == '1') {
            name_val += (uint8_t)pow(2, inc);
        }
        inc++;
    }

    inc = -1;

    // Now regs:
    for (int i = reg_length-1; i > -1; i--) {
        if (reg_combined[i] == '1') {
            reg_val += (uint8_t)pow(2, inc);
        }
        inc++;
    } 

    // To get the number hehe...
    // Since name (upcode 1 and 2) are the 4 most significant bits
    // we multiply by 16, since it is base 16.
    // Then add the register bits to it.
    name_val *= 16;
    name_val += reg_val;

    free(reg_combined);
    return name_val;
}

/// @brief Sepperates each instruction by: NAME R1 RST2, so that they can me mapped.
/// Then uses instr_to_uint_8b to convert the split instruction into a uint.
void sepperate_instructions() {
    int num_instructions = count_instructions(PROGRAM_PATH);
    if (num_instructions <= 0) {
        printf("Number of instructions is less then or equal 0: %d\n", num_instructions);
        exit(EXIT_FAILURE);
    }

    char* temp[num_instructions];

    // Gets the first instruction.
    temp[0] = strtok(instrs, "\n");
    // Loads every instruction after the first into temp
    for (int i = 1; i < num_instructions; i++) {
        temp[i] = strtok(NULL, "\n");
    }

    // NEEDS EXPLANATION!
    for (int i = 0; i < num_instructions; i++) {

        // Holds the binary sequences of an instruction.
        // Name: Binary representation of the name (Upcode 1 and 2).
        // R1: binary representation of the first register input.
        // Rst2: binary representation of the second input (register/immidiate).
        struct instr_to_8bit* res = malloc(sizeof(struct instr_to_8bit));
        assert(res != NULL);

        // Holds the current instructions 'iargs':
        // Name: Name of instruction as char*.
        // Upcodes_4b: Upcode1 and 2 as a char*.
        // Num_args: Number of arguments for the current instruction.
        struct instr_args* iargs = malloc(sizeof(struct instr_args));
        assert(iargs != NULL);

        // Gets upcode 1 and 2 that matches the name of the instruction.
        // Saves it in iargs.
        iargs->name = strtok(temp[i], " ");
        get_upcodes(iargs);

        switch (iargs->num_args) {
        // Only HLT has 0 args.
        case 0:
            res->name = iargs->upcodes_4b;
            res->r1 = DEFAULT_REG_VAL;
            res->rst2 = DEFAULT_REG_VAL;
            break;
        case 1:
            res->name = iargs->upcodes_4b;

            char* t = strtok(NULL, " ");
            res->r1 = get_regs(t);
            res->rst2 = DEFAULT_REG_VAL;
            break;
        case 2:
            res->name = iargs->upcodes_4b;

            char* t1 = strtok(NULL, " ");
            res->r1 = get_regs(t1);

            char* t2 = strtok(NULL, " ");
            res->rst2 = get_regs(t2);
            break;
        default:
            printf("Error in mapping arguments to binary.\n");
            break;
        }

        // Gets the integer value of the instruction
        // and stores it in p.
        uint8_t int_val = binary_to_uint_8b(res);
        p[i] = int_val;
        free(res);
        free(iargs);
    }

}

/// @brief Prints all instructions as strings.
void print_instr_split() {
    printf("%s\n", instrs);
}


// Initializes memory and 
// writes the program instructions as uints to memory.
// The first 64 bytes are free
// the last 192 bytes are reserved for instructions

/// @brief Initializes memory, reads and parses the program
/// and writes the program to memory.
void get_program() {
    int cnt = count_instructions(PROGRAM_PATH);


    init_memory();
    read_program_file();


    p = malloc(sizeof(uint8_t) * cnt);
    sepperate_instructions(p);

    for (int i = 0; i < cnt; i++) {
        write_memory(PROG_START_ADDR + i, p[i]);
    }

    // print_memory();

    free(p);
}


