#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2]; // Descriptores de archivo para la tubería: fd[0] leer, fd[1] escribir
    pid_t pid;
    int inicio = 1, fin = 100; // Rango de ejemplo: 1 a 100
    long long suma = 0;

    // Crear la tubería
    if (pipe(fd) == -1) {
        perror("falló la tubería");
        exit(1);
    }

    // Crear el proceso hijo
    pid = fork();
    if (pid < 0) {
        perror("falló el fork");
        exit(1);
    }

    if (pid == 0) { // Proceso hijo
        close(fd[0]); // Cerrar extremo de lectura
        // Calcular la suma
        for (int i = inicio; i <= fin; i++) {
            suma += i;
        }
        // Escribir la suma en la tubería
        if (write(fd[1], &suma, sizeof(suma)) == -1) {
            perror("falló la escritura");
            exit(1);
        }
        close(fd[1]); // Cerrar extremo de escritura
        exit(0); // El hijo termina
    } else { // Proceso padre
        close(fd[1]); // Cerrar extremo de escritura
        wait(NULL); // Esperar a que el hijo termine
        // Leer la suma de la tubería
        if (read(fd[0], &suma, sizeof(suma)) == -1) {
            perror("falló la lectura");
            exit(1);
        }
        printf("La suma de los números desde %d hasta %d es: %lld\n", inicio, fin, suma);
        close(fd[0]); // Cerrar extremo de lectura
    }

    return 0;
}