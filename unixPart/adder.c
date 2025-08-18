#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]); // Longitud del rango
    if (n < 3) {
        fprintf(stderr, "n debe ser al menos 3\n");
        exit(1);
    }

    int num_hijos = n / 3; // Número de procesos hijos
    int fd[num_hijos][2]; // Arreglo de tuberías para cada hijo
    pid_t pids[num_hijos];
    long long suma_total = 0;

    // Crear tuberías para cada hijo
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
            int inicio = i * (n / num_hijos) + 1;
            int fin = (i == num_hijos - 1) ? n : (i + 1) * (n / num_hijos);
            long long suma = 0;
            for (int j = inicio; j <= fin; j++) {
                suma += j;
            }
            // Escribir la suma en la tubería
            if (write(fd[i][1], &suma, sizeof(suma)) == -1) {
                perror("falló la escritura");
                exit(1);
            }
            close(fd[i][1]); // Cerrar extremo de escritura
            exit(0);
        }
    }

    // Proceso padre
    for (int i = 0; i < num_hijos; i++) {
        close(fd[i][1]); // Cerrar extremo de escritura
        waitpid(pids[i], NULL, 0); // Esperar a cada hijo
        long long suma_parcial;
        if (read(fd[i][0], &suma_parcial, sizeof(suma_parcial)) == -1) {
            perror("falló la lectura");
            exit(1);
        }
        suma_total += suma_parcial;
        close(fd[i][0]); // Cerrar extremo de lectura
    }

    printf("La suma total de los números del 1 al %d es: %lld\n", n, suma_total);
    return 0;
}
