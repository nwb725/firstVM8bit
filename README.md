# firstVM8bit
A small 8 bit VM for fun.

Consists of a CPU, memory, an assembler and a utility file. It is possible to run my own
defined 8bit instruction set, allthough with some limitations.

It uses a multibyte instruction set:

FIRST BYTE: 
    - First 4 bits are upcode.
    - Last 4 bits are for the destination register.

SECOND BYTE:
    - Case it uses an immidiate, this then hold the immidiate (up to 1byte).
    - Case it uses a register then the 4 least significant bits are the accumulator register.

*INSTRUCTION SET*
    - LDI r1 imm: Loads immidiate into register.
    - LD r1 r2: Loads value from memory[r2] and stores in r1.
    - ST r1 r2: Stores value in r1 in memory[r2].
    - MOV r1 r2: Moves value from r2 into r1.

    - ADD r1 r2: Adds values in r1 with r2, stores it in r1.
    - SUB r1 r2: Subtracts value in r2 from r1, stores in r1.
    - MUL r1 r2: Mulliplies values in r1 with r2, stores in r1.
    - ADDI r1 imm: Adds value in r1 with immidiate, stores in r1.

    - AND r1 r2: Bitwise ands value in r1 with value in r2, stores in r1.
    - OR r1 r2: Bitwise ors value in r1 with value in r2, stores in r1.
    - XOR r1 r2: Bitwise xors value in r1 with value in r2, stores in r1.
    - NOT r1 r2: Bitwise nots value in rst2, stores in r1.

    - JMP r1: Jumps to address addr[r1].
    - JMPZ r1 r2: Jumps to addr[rst2] ONLY IF value in r1 is zero.
    - JMPNZ r1 r2: Jumps to addr[rst2] ONLY IF value in r1 is NOT zero.
    - HLT: Stops the program.


