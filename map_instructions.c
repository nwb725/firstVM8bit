#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the file content into instrs buffer
    size_t read_bytes = fread(instrs, 1, sizeof(instrs) - 1, prg_stream);

    // Null-terminate the string
    instrs[read_bytes] = '\0';

    fclose(prg_stream);
}

struct instr_to_8bit* sepperate_instructions() {
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

    // Create an instr_args struct with the name
    // And get the 4bit upcodes and number of args.
    // Loop through all the sepperated instructions
    for (int i = 0; i < num_instructions-1; i++) {
        char* r = malloc(5+1);
        r[0] = "\0";
        struct instr_args* iargs = malloc(sizeof(struct instr_args));
        iargs->name = strtok(temp[i], " ");
        struct instr_args* curr = get_upcodes(iargs);
        for (int j = 0; j < curr->num_args; j++) {
            char* temp1 = strtok(NULL, " ");
            temp1 = get_regs(temp1);
            printf("%s\n", r);
            strcat(r, temp1);
        }
        //printf("%s\n", r);
        //printf("Name: %s, Num args: %d, Upcodes: %s.\n",curr->name, curr->num_args, curr->upcodes_4b);
        free(iargs);
    }

    

    /* char* t  = strtok(temp[0], " ");
    char* t2 = strtok(NULL, " ");
    char* t3 = strtok(NULL, " ");
    char* t4 = strtok(NULL, "\0");
    printf("%s\n", t);
    printf("%s\n", t2);
    printf("%s\n", t3); */
    //printf("%s\n", t4);
    return NULL;
}

void print_instr_split() {
    sepperate_instructions();
    //printf("%s\n", instrs);
}


