#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vm.h"
#include "map_instructions.h"

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
void generate_split_instr() {


}

void sepperate_instructions() {
    int num_instructions = count_instructions(PROGRAM_PATH);
    char* temp[num_instructions];

    // Gets the first instruction.
    temp[0] = strtok(instrs, "\n");

    // Loads every instruction after the first into temp
    for (int i = 1; i < num_instructions; i++) {
        temp[1] = strtok(NULL, "\n");
    }

    // The HLT instruction matches on "HLT" and "HLT\0" 
    // But not on "HLT\n" or "HLT ".
    if (!strcmp(temp[0], "ADD r1 rst2")) {
        printf("yeah\n");
    }
}

void print_instr_split() {
    sepperate_instructions();
    //printf("%s\n", instrs);
}


