//
// Created by jpmar on 11/05/2025.
//
// Using 'extern' data

// You should write a function called bump() that uses an extern variable so that the first time it is called,
// it returns int 0, the next time it returns 1 and so on.

#include <stdio.h>

extern int call = 0;

int main() {
    int bump();
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
}

int bump() {
    int call0;
    call0 = call;
    call++;
    return call0;
}