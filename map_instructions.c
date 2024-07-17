#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "vm.h"

// ADD r1 r2
// ADDI r3 23
// HLT

// Read from the .txt file.
// Create a list of instructions that end an '\n'.
// Map the instruction name and registers/immidiates to hex.
// Returns a program of 8bit instructions for 'prog[]' in VM.
