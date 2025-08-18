#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Leer números desde la entrada estándar
    int n = 0;
    int capacidad = 100; // Capacidad inicial para el arreglo dinámico
    int *numeros = malloc(capacidad * sizeof(int));
    if (!numeros) {
        perror("falló malloc");
        exit(1);
    }

    // Leer números hasta EOF
    int num;
    while (scanf("%d", &num) != EOF) {
        if (n >= capacidad) {
            capacidad *= 2;
            numeros = realloc(numeros, capacidad * sizeof(int));
            if (!numeros) {
                perror("falló realloc");
                exit(1);
            }
        }
        numeros[n++] = num;
    }

    if (n < 3) {
        fprintf(stderr, "Se necesitan al menos 3 números\n");
        free(numeros);
        exit(1);
    }

    int num_hijos = n / 3;
    int fd[num_hijos][2];
    pid_t pids[num_hijos];
    long long suma_total = 0;

    // Crear tuberías
    for (int i = 0; i < num_hijos; i++) {
        if (pipe(fd[i]) == -1) {
            perror("falló la tubería");
            exit(1);
        }
    }

    // Crear n/3 procesos hijos
    for (int i = 0; i < num_hijos; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("falló el fork");
            exit(1);
        }
        if (pids[i] == 0) { // Proceso hijo
            close(fd[i][0]); // Cerrar extremo de lectura
            // Calcular el rango para este hijo
            int inicio = i * (n / num_hijos);
            int fin = (i == num_hijos - 1) ? n : (i + 1) * (n / num_hijos);
            long long suma = 0;
            for (int j = inicio; j < fin; j++) {
                suma += numeros[j];
            }
            // Escribir la suma en la tubería
            if (write(fd[i][1], &suma, sizeof(suma)) == -1) {
                perror("falló la escritura");
                exit(1);
            }
            close(fd[i][1]);
            exit(0);
        }
    }

    // Proceso padre
    for (int i = 0; i < num_hijos; i++) {
        close(fd[i][1]); // Cerrar extremo de escritura
        waitpid(pids[i], NULL, 0);
        long long suma_parcial;
        if (read(fd[i][0], &suma_parcial, sizeof(suma_parcial)) == -1) {
            perror("falló la lectura");
            exit(1);
        }
        suma_total += suma_parcial;
        close(fd[i][0]);
    }

    printf("La suma total de %d números es: %lld\n", n, suma_total);
    free(numeros);
    return 0;
}