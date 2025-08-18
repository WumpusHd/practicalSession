#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "n debe ser positivo\n");
        exit(1);
    }

    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Generar e imprimir n números aleatorios
    for (int i = 0; i < n; i++) {
        printf("%d ", rand() % 100 + 1); // Números aleatorios entre 1 y 100
    }
    printf("\n");

    return 0;
}