#include "memory.h"
#include "cpu.h"
#include "assembler.h"
#include "interface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// TODO: CLI.
// Step 1: Initialize the VM, init registers, memory and so on.
// Step 2: Let the user decide and be able to interact with the VM:
// COMMANDS:
//        BASIC:
//      - load <filename> => Loads a .txt file into memory.
//      - run => Runs the current program, until an error or HLT.
//      - step => Step executes 1 instruction (The next).
//      - reset => Resets the VM to the intial state.
//      - exit => Exits the CLI tool.
//
//        INSPECTION:
//      - regs => Displays the value of all registers
//      - mem <addr> <len> => Displays all memory from addr to addr + len.
//      - break <addr> => Sets a breakpoint at addr.
//      - clear <addr> => Clears a breakpoint at addr.
//      - peak <addr> => Look at memory at addr.
//      - poke <addr> <val> => Overwrites memory at addr with val.
//
//        MORE ADVANCED:
//      - trace <on | off> => Traces and logs the program.


/// @brief Resets the virtual machine to initial state. 
void vm_reset() {
    reset_memory();
    reset_regs();
}

/// @brief Loads a .txt file into memory.
/// @param fname Name of file to load into memory.
void vm_load(char* fname) {
    read_program_file(fname);
    get_program(fname);
    printf("Program from '%s' successfully written to memory!\n", fname);
}

/// @brief Executes the program that is stored in memory.
void vm_run_prog() {
    run_program();
}

/// @brief Terminates the VM.
void vm_exit() {
    exit(EXIT_SUCCESS);
}

/// @brief Prints all registers and their values.
void vm_regs() {
    print_regs();
}

/// @brief Prints memory.
void vm_mem() {
    print_memory();
}

/// @brief Gives the user a list of commands.
void vm_help() {
    printf("\n");
    printf("BASIC:\n");
    printf("  + load <filename> => Loads a .txt file into memory.\n");
    printf("  + run => Runs the current program, until an error or HLT.\n");
    printf("  - step => Step executes 1 instruction (The next).\n");
    printf("  + reset => Resets the VM to the initial state.\n");
    printf("  + exit => Exits the CLI tool.\n");
    printf("\n");
    printf("INSPECTION:\n");
    printf("  + regs => Displays the value of all registers.\n");
    printf("  + mem <addr> <len> => Displays all memory from addr to addr + len.\n");
    printf("  - break <addr> => Sets a breakpoint at addr.\n");
    printf("  - clear <addr> => Clears a breakpoint at addr.\n");
    printf("  - peak <addr> => Look at memory at addr.\n");
    printf("  - poke <addr> <val> => Overwrites memory at addr with val.\n");
    printf("\n");
    printf("MORE ADVANCED:\n");
    printf("  - trace <on | off> => Traces and logs the program.\n");
    printf("\n");
}

void read_input(char* in) {
    char* command = strtok(in, " ");
    if (strcmp(command, "load") == 0) {
        char ext[50];
        char* f = strtok(NULL, " ");
        strcpy(ext, FPATH);
        strcat(ext, f);
        vm_load(ext);
        print_instr_split();
    }
    if (strcmp(command, "exit") == 0) {
        vm_exit();
    }
    if (strcmp(command, "run") == 0) {
        vm_run_prog();
    }
    if ((strcmp(command, "regs") == 0)) {
        vm_regs();
    }
    if ((strcmp(command, "mem") == 0)) {
        if (strtok(NULL, " ") == NULL) {
            vm_mem();
        }
    }
    if ((strcmp(command, "help") == 0)) {
        vm_help();
    }
    else {
        //printf("Invalid prompt, type 'help' for a list of commands.\n");
    }
    
}