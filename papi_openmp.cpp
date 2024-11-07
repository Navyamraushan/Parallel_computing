#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>
#include "papi.h"

using namespace std;
// using namespace std::chrono;

// Function to generate a random matrix of size rows x cols
vector<vector<int>> generateMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100; // Random numbers between 0 and 99
        }
    }
    return matrix;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {

   int s1 = PAPI_get_real_usec();
    srand(time(0)); // Seed for random number generation

    int n, m, p;
    cout << "Enter the number of rows for Matrix A: ";
    cin >> n;
    cout << "Enter the number of columns for Matrix A / rows for Matrix B: ";
    cin >> m;
    cout << "Enter the number of columns for Matrix B: ";
    cin >> p;

    // Generate random matrices A and B
    vector<vector<int>> A = generateMatrix(n, m);
    vector<vector<int>> B = generateMatrix(m, p);
    vector<vector<int>> C(n, vector<int>(p, 0)); // Resultant matrix

    // Start timing the execution
    // auto start = high_resolution_clock::now();

    // Parallel matrix multiplication
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Stop timing the execution
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(stop - start);

    // Print the matrices and the result
    cout << "Matrix A:\n";
    printMatrix(A);

    cout << "\nMatrix B:\n";
    printMatrix(B);

    cout << "\nResultant Matrix C (A * B):\n";
    printMatrix(C);

    int s2 = PAPI_get_real_usec();

    // Print execution time
    cout << "\nExecution time: " <<s2-s1 << " milliseconds\n";

    return 0;
}
// to ruln this file
// mpic++ papi_openmp.cpp -o mcpp -lpapi -I/home/adityasr/Desktop/papi-7.2.0b1/src/bin/include
// mpirun -np 4 ./mcpp
