#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

#define SIZE 40

// Estructura para pasar datos a los hilos
struct MatrixData {
    int a[SIZE][SIZE];
    int b[SIZE][SIZE];
    int result[SIZE][SIZE];
};

// Hilo para sumar matrices
void* sum_matrices(void* arg) {
    MatrixData* data = (MatrixData*)arg;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            data->result[i][j] = data->a[i][j] + data->b[i][j];
    pthread_exit(NULL);
}

// Hilo para restar matrices
void* diff_matrices(void* arg) {
    MatrixData* data = (MatrixData*)arg;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            data->result[i][j] = data->a[i][j] - data->b[i][j];
    pthread_exit(NULL);
}

// Multiplicar matrices
void multiply_matrices(int result[SIZE][SIZE], int sum[SIZE][SIZE], int diff[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
                result[i][j] += sum[i][k] * diff[k][j];
        }
    }
}

int main() {
    clock_t start = clock();
    srand(time(0));
    int matrix_a[SIZE][SIZE], matrix_b[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            matrix_a[i][j] = rand() % 2;
            matrix_b[i][j] = rand() % 2;
        }

    MatrixData sum_data, diff_data;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            sum_data.a[i][j] = matrix_a[i][j];
            sum_data.b[i][j] = matrix_b[i][j];
            diff_data.a[i][j] = matrix_a[i][j];
            diff_data.b[i][j] = matrix_b[i][j];
        }

    // Crear hilos
    pthread_t sum_thread, diff_thread;
    if (pthread_create(&sum_thread, NULL, sum_matrices, &sum_data)) {
        std::cout << "Error creando hilo suma\n";
        return 1;
    }
    if (pthread_create(&diff_thread, NULL, diff_matrices, &diff_data)) {
        std::cout << "Error creando hilo resta\n";
        return 1;
    }

    // Esperar a los hilos
    pthread_join(sum_thread, NULL);
    pthread_join(diff_thread, NULL);

    // Multiplicar resultados
    int final_result[SIZE][SIZE];
    multiply_matrices(final_result, sum_data.result, diff_data.result);

    // Medir tiempo
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Tiempo con hilos: " << time_spent << " segundos\n";

    // Imprimir resultado
    std::cout << "Resultado final (producto):\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            std::cout << final_result[i][j] << " ";
        std::cout << "\n";
    }

    return 0;
}