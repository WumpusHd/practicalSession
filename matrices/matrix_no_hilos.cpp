#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 40

void sum_matrices(int a[SIZE][SIZE], int b[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result[i][j] = a[i][j] + b[i][j];
}

void diff_matrices(int a[SIZE][SIZE], int b[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result[i][j] = a[i][j] - b[i][j];
}

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
    // Medir tiempo
    clock_t start = clock();

    srand(time(0));
    int matrix_a[SIZE][SIZE], matrix_b[SIZE][SIZE], sum_result[SIZE][SIZE], diff_result[SIZE][SIZE], final_result[SIZE][SIZE];

    // Llenar matrices
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            matrix_a[i][j] = rand() % 2;
            matrix_b[i][j] = rand() % 2;
        }

    // Calcular suma y resta
    sum_matrices(matrix_a, matrix_b, sum_result);
    diff_matrices(matrix_a, matrix_b, diff_result);
    multiply_matrices(final_result, sum_result, diff_result);

    // Medir tiempo
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Tiempo sin hilos: " << time_spent << " segundos\n";

    // Imprimir resultado
    std::cout << "Resultado final (producto):\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            std::cout << final_result[i][j] << " ";
        std::cout << "\n";
    }

    return 0;
}