#ifndef INTERFACE_H
#define INTERFACE_H

#define FPATH "../firstVM8bit/"
#define ON 1
#define OFF 0
#define EMPTY 0
#define MAX_COMMAND_ARG_SIZE 200

struct command {
    char *name;
    char *args;
};


/// TODO: Finish, the idea is to keep track of the state of the vm.
struct state {
    int mem_empty;
    int tracing;
    int exit;
};

void read_input(char *in);
void vm_run();
#endif