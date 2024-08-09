#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symtab.h"

/// IMPORTANT! <FIXED>
/// The stack logic is not working, the returns are opposite? 
/// Need to look at how the RET is working.

/// The order in which the labels are written, jumped to at returned from matter.
/// If the labels are added as: L1 -> L2 -> L3:
/// Then the call order must be L3 -> L2 -> L1.

struct f_label* stack[MAX_STACK_SIZE];
int stack_ptr = 0;

/// @brief Initialized the stack, the stack is a symbol table that holds function names and addresses.
void stack_init() {
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        stack[i] = (struct f_label*)malloc(sizeof(struct f_label));
    }
}

/// @brief Pops an item off the stack and returns that items call address.
uint8_t stack_pop() {
    if (stack_ptr == 0) {
        printf("Cant pop from an empty stack.\n");
        exit(EXIT_FAILURE);
    }
    return stack[--stack_ptr]->r_addr;
}

/// @brief Adds a return address to a label.
/// @param addr The return address to add.
/// @param name The label which the return should be added to.
void stack_add_return(uint8_t addr, char* name) {
    for (int i = 0; i < stack_ptr; i++) {
        if (strcmp(stack[i]->name, name) == 0) {
            stack[i]->r_addr = addr;
            break;
        }
    }
}

/// @brief Pushes an item on to the stack. Only works if stack is not full.
/// @param in The item you want to push to the stack.
void stack_push(struct f_label* in) {
    if (stack_ptr >= MAX_STACK_SIZE) {
        printf("Stack is full, tried to add: %s.\n", in->name);
        exit(EXIT_FAILURE);
    } 
    if (stack_ptr < 0) {
        printf("Stack pointer is below zero?, should never land here.\n");
        exit(EXIT_FAILURE);
    }
    stack[stack_ptr]->name = in->name;
    stack[stack_ptr]->addr = in->addr;
    stack_ptr++;
}

/// @brief Destroys the stack. Deallocates the whole stack. 
/// @attention MUST BE CALLED!
void stack_destroy() {
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        free(stack[i]);
    }
}

/// @brief Removing the MAIN label from the label stack. 
/// Finds where in the stack NAME is, removes it and moves everything down.
void stack_rmv_main() {
    int indx;
    for (int i = 0; i < stack_ptr; i++) {
        if (strcmp(stack[i]->name, "MAIN") == 0) {
            indx = i;
            break;
        }
    }

    for (int i = indx; i < stack_ptr - 1; i++) {
        stack[i]->name = stack[i+1]->name;
        stack[i]->addr = stack[i+1]->addr;
    }

    stack_ptr--;
}

/// @brief Looks up a function name in the symtab.
/// @param name The name of the function label.
/// @return Returns the address of the function on success, returns 0 if the symtab does not contain the label.
uint8_t stack_lookup(char* name) {
    for (int i = 0; i < stack_ptr; i++) {
        if (strcmp(name, stack[i]->name) == 0) {
            return stack[i]->addr;
        }
    }
    return 0;
}

/// @brief Counts number of elements in the stack.
/// @return Returns the number of elements in the stack.
int stack_count() {
    return stack_ptr;
}

/// @brief Prints the content of the stack
void stack_print() {
    for (int i = 0; i < stack_ptr; i++) {
        printf("Index: %d, Name: %s, Addr: %d, r_Addr: %d\n", i, stack[i]->name, stack[i]->addr, stack[i]->r_addr);
    }
}