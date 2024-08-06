#include "cpu.h"
#include "assembler.h"
#include "memory.h"
#include "interface.h"
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    init_regs();
    init_memory();
    while (1)
    {
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

    return 0;
}