#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdint.h>

#define MAX_STACK_SIZE 10

struct f_label {
    char* name;
    uint8_t addr;
};

void stack_init();
struct f_label* stack_pop();
void stack_push(struct f_label*);
void stack_destroy();
void stack_print();
uint8_t stack_lookup(char*);
int stack_count();

#endif