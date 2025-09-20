//
// Created by jpmar on 11/05/2025.
//
// Cáculo de fatorial por recursividade

#include <stdio.h>
#include <stdlib.h>

int fatorial(int n) {
    if (n == 0 || n == 1) // Caso base: fatorial de 0 ou 1 é 1
        return 1;
    else
        return n * fatorial(n - 1); // Chamada recursiva
}

int main() {
    printf("Please insert a positive-integer number:  \n");
    int num;
    scanf("%d", &num);
    printf("Fatorial of %d is %d\n", num, fatorial(num));
}
