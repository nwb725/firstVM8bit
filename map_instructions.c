#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "vm.h"
#include "map_instructions.h"
#include "map_helpers.h"

// ADD r1 r2
// ADDI r3 23
// HLT

// Read from the .txt file.
// Create a list of instructions that end an '\n'.
// Map the instruction name and registers/immidiates to hex.
// Returns a program of 8bit instructions for 'prog[]' in VM.

char instrs[255];

uint8_t* p;

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

uint8_t binary_to_hex_8b(struct instr_to_8bit* in) {

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

    //printf("%ld\n", name_length);
    // First name:
    for (int i = name_length-1; i > -1; i--) {
        if (in->name[i] == '1') {
            name_val += (uint8_t)pow(2, inc);
            // printf("INC: %d\n", inc);
        }
        inc++;
    }
    // printf("Name value: %d\n", name_val);

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
    return name_val;
}


void sepperate_instructions(uint8_t* r) {
    int num_instructions = count_instructions(PROGRAM_PATH);
    if (num_instructions <= 0) {
        printf("Number of instructions is less then or equal 0: %d", num_instructions);
        exit(EXIT_FAILURE);
    }

    char* temp[num_instructions];

    // Gets the first instruction.
    temp[0] = strtok(instrs, "\n");
    // Loads every instruction after the first into temp
    for (int i = 1; i < num_instructions; i++) {
        temp[i] = strtok(NULL, "\n");
    }

    // The HLT instruction matches on "HLT" and "HLT\0" 
    // But not on "HLT\n" or "HLT ".

    // NEEDS EXPLANATION!
    for (int i = 0; i < num_instructions; i++) {

        // Holds the binary sequences of an instruction.
        // Name: Binary representation of the name (Upcode 1 and 2).
        // R1: binary representation of the first register input.
        // Rst2: binary representation of the second input (register/immidiate).
        struct instr_to_8bit* res = malloc(sizeof(struct instr_to_8bit));

        // Holds the current instructions 'iargs':
        // Name: Name of instruction as char*.
        // Upcodes_4b: Upcode1 and 2 as a char*.
        // Num_args: Number of arguments for the current instruction.
        struct instr_args* iargs = malloc(sizeof(struct instr_args));

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
            printf("Error in mapping arguments to binary.");
            break;
        }
        printf("Full instrs: %s %s%s\n", res->name, res->r1, res->rst2);
        uint8_t int_val = binary_to_hex_8b(res);
        r[i] = int_val;
        free(res);
        free(iargs);
    }

}

void print_instr_split() {
    printf("%s\n", instrs);
}


// Needs to return something good?? Segfaults.
uint8_t* get_program() {
    p = malloc(sizeof(uint8_t) * count_instructions(PROGRAM_PATH));
    sepperate_instructions(p);
    return p;
}


