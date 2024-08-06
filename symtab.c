#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symtab.h"


struct f_label* stack[MAX_STACK_SIZE];
int stack_ptr = 0;

/// @brief Initialized the stack, the stack is a symbol table that holds function names and addresses.
void stack_init() {
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        stack[i] = (struct f_label*)malloc(sizeof(struct f_label));
    }
}

/// @brief Pops an item off the stack and returns that item.
struct f_label* stack_pop() {
    if (stack_ptr == 0) {
        printf("Cant pop from an empty stack.\n");
        exit(EXIT_FAILURE);
    }
    return stack[--stack_ptr];
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

/// @brief Looks up a function name in the symtab.
/// @param name The name of the function label.
/// @return Returns the address of the function on success, returns -1 if the symtab does not contain the label.
uint8_t stack_lookup(char* name) {
    for (int i = 0; i < stack_ptr; i++) {
        if (strcmp(name, stack[i]->name) == 0) {
            printf("LOOKUP\n");
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
        printf("Index: %d, Name: %s, Addr: %d\n", i, stack[i]->name, stack[i]->addr);
    }
}