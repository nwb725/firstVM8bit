#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdint.h>

#define MAX_STACK_SIZE 10

struct f_label {
    char* name;
    uint8_t addr;
    uint8_t r_addr;
};

void stack_init();
uint8_t stack_pop();
void stack_push(struct f_label*);
void stack_destroy();
void stack_print();
uint8_t stack_lookup(char*);
int stack_count();
void stack_rmv_main();
void stack_add_return(uint8_t, char*);

#endif