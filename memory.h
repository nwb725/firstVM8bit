#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 256

void init_memory();
void write_memory(uint8_t address, uint8_t value);
uint8_t read_memory(uint8_t address);
void print_memory();

#endif // MEMORY_H