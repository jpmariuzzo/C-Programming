//
// Created by jpmar on 11/05/2025.
//

// LBS290 Exercise 18 - A Simple Machine. You are to implement an interpreter for a simple programming language.
// Your computer has 256 characters of memory. You are to read a sequence of instructions from input and perform
// those instructions. At the end of the program you print the memory out as a zero-terminated C character array.
// Here are the instructions you need to support:

// *           This is a comment, print it out and do no further processing
// X           Exit the program (end-of-input also ends the program)
// 5 = 42      Put the number 42 into memory[5]
// 10 + 3      Add 3 to the contents of memory[10]
// 7 - 1       Suptract 1 from the contents of memory[7]
// All of the numbers should be in the range of 0-255 so they fit into a C char variable.
// Fun Fact:Dr. Chuck used an assignment similar to this one while teaching C - LBS 290 - Fall 1991.

#include <stdio.h>

int main()
{
    char line[256]; // Array to get the lines
    char memory[256]; // Array to create a memory
    char opcode;
    int count,address,value;

    while(fgets(line, 256, stdin) != NULL) {
        //printf("\nLine: %s\n",line);
        if ( line[0] == 'X' ) break;
        if ( line[0] == '*' ) {
            printf("%s",line);
            continue;
        }
        count = sscanf(line, "%d %c %d", &address, &opcode, &value);
        if ( count != 3 ) continue; // Checking the items of a command line. It has to be 3.
        //printf("address: %d opcode: %c value: %d\n", address, opcode, value);

        if (opcode == '=') memory[address] = value;
        if (opcode == '+') memory[address] += value;
        if (opcode == '-') memory[address] -= value;

        //printf("Memory:\n%s\n", memory);
    }
    printf("Memory:\n%s\n", memory);
}