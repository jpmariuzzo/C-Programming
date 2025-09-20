#include <stdio.h>

/* Função para calcular o tamanho da palavra */
int word_len() {
    char c;
    int len = 0;
    
    // Lê caracteres até encontrar um delimitador de palavra (espaço, tabulação ou nova linha)
    while ((c = getchar()) != ' ' && c != '\n' && c != '\t' && c != EOF) {
        ++len;
    }
    
    return len;
}

int main() {
    int size;
    printf("Digite uma palavra: ");
    size = word_len();  // Chama a função para medir o tamanho da palavra
    char hist[size];
    for(int i=0; i < size; i++) {
        hist[i] = '#';
    }
    printf("O tamanho da palavra é: %d\n", size);
    printf("Histograma: %s\n", hist);
    
}
