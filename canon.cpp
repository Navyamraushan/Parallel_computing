#include <iostream>
#include <omp.h>

void multiplyMatrices(const int A[3][3], const int B[3][3], int C[3][3]) {
    int n = 3;
    int tempA[3][3], tempB[3][3];

    // Initialize result matrix C to zero
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
        }
    }

    // Initial alignment of A and B
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            tempA[i][(j + i) % n] = A[i][j];
            tempB[(i + j) % n][j] = B[i][j];
        }
    }

    // Perform the multiplication
    for (int step = 0; step < n; ++step) {
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                C[i][j] += tempA[i][j] * tempB[i][j];
            }
        }

        // Shift tempA left by one and tempB up by one
        int newTempA[3][3], newTempB[3][3];
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                newTempA[i][j] = tempA[i][(j + 1) % n];
                newTempB[i][j] = tempB[(i + 1) % n][j];
            }
        }

        #pragma omp parallel for collapse(2)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                tempA[i][j] = newTempA[i][j];
                tempB[i][j] = newTempB[i][j];
            }
        }
    }
}

int main() {
    int A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int C[3][3];

    // Perform matrix multiplication using Canon's algorithm
    multiplyMatrices(A, B, C);

    // Print the result matrix
    std::cout << "Result matrix:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

// to run this code
// g++ -fopenmp canon.cpp -o canon
