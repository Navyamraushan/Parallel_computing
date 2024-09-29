#include <iostream>
#include <omp.h>
using namespace std;

void initialize_matrix(int **matrix, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

int** allocate_matrix(int n) {
    int **matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    return matrix;
}

void deallocate_matrix(int **matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void matrix_multiply(int **a, int **b, int **c, int n) {
    // Initialize matrix c with zeros
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = 0;
        }
    }

    // Multiply matrices a and b
    #pragma omp parallel for collapse(3)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
    int n = 10;
    int **a = allocate_matrix(n);
    int **b = allocate_matrix(n);
    int **c = allocate_matrix(n);

    initialize_matrix(a, n);
    initialize_matrix(b, n);

    matrix_multiply(a, b, c, n);

    // Optionally, print the result matrix c
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    deallocate_matrix(a, n);
    deallocate_matrix(b, n);
    deallocate_matrix(c, n);

    return 0;
}

