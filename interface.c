#include "memory.h"
#include "cpu.h"
#include "assembler.h"
#include "interface.h"
#include "symtab.h"
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

uint8_t entry = PROG_START_ADDR;

/// @brief Parses the user input.
struct command *parse_command(char *in)
{
    struct command *c = malloc(sizeof(struct command));
    char *c_name = strtok(in, " ");
    char *c_arg = strtok(NULL, " ");

    c->name = c_name;

    if (c_arg == NULL) {
        return c;
    }

    c->args = c_arg;
    return c;

    printf("Error in parsing commands. Got: <%s>, from user", in);
    exit(EXIT_FAILURE);
}

void p_vm_init() {
    init_regs();
    init_memory();
}


void vm_cleanup() {
    /// TODO: Should clean up allocations.
}

/// @brief Resets the virtual machine to initial state.
void vm_reset() {
    reset_memory();
    reset_regs();
}

/// @brief Loads a .txt file into memory.
/// @param fname Name of file to load into memory.
void vm_load(char *fname) {
    read_program_file(fname);
    entry = get_program(fname);
    stack_print();
    printf("Program from '%s' successfully written to memory!\n", fname);
}

/// @brief Executes the program that is stored in memory.
void vm_run_prog() {
    run_program(entry);
}

/// @brief Terminates the VM.
void vm_exit() {
    /// TODO: Sets state->exit = TRUE, runs cleanup.
    vm_cleanup();
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

void read_input(char *in) {
    struct command *command = parse_command(in);
    if (strcmp(command->name, "load") == 0) {
        char buf[MAX_COMMAND_ARG_SIZE];
        strcpy(buf, FPATH);
        strcat(buf, command->args);
        vm_load(buf);
    }
    if (strcmp(command->name, "exit") == 0) {
        vm_exit();
    }
    if (strcmp(command->name, "run") == 0) {
        vm_run_prog();
    }
    if ((strcmp(command->name, "regs") == 0)) {
        vm_regs();
    }
    if ((strcmp(command->name, "reset") == 0)) {
        vm_reset();
    }
    if ((strcmp(command->name, "mem") == 0)) {
        if (strtok(NULL, " ") == NULL)
        {
            vm_mem();
        }
    }
    if ((strcmp(command->name, "help") == 0)) {
        vm_help();
    }
    else {
        // printf("Invalid prompt, type 'help' for a list of commands.\n");
    }
    free(command);
}

void vm_run() {
    p_vm_init();
    vm_help();
    while (1) {
        printf("Type command or 'exit' to quit: ");
        char c[50];
        fgets(c, sizeof(c), stdin);
        size_t len = strlen(c);
        if (len > 0 && c[len - 1] == '\n')
        {
            c[len - 1] = '\0';
        }
        read_input(c);
    }
}