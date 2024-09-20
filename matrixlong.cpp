#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<vector<long long>> generateMatrix(int rows, int cols) {
    vector<vector<long long>> matrix(rows, vector<long long>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100; // Random numbers between 0 and 99
        }
    }
    return matrix;
}

void printMatrix(const vector<vector<long long>>& matrix) {
    for (const auto& row : matrix) {
        for (long long val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // Seed for random number generation

    int n, m, p;
    cout << "Enter the number of rows for Matrix A: ";
    cin >> n;
    cout << "Enter the number of columns for Matrix A / rows for Matrix B: ";
    cin >> m;
    cout << "Enter the number of columns for Matrix B: ";
    cin >> p;

    vector<vector<long long>> A = generateMatrix(n, m);
    vector<vector<long long>> B = generateMatrix(m, p);
    vector<vector<long long>> C(n, vector<long long>(p, 0));

    auto start = high_resolution_clock::now();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Matrix A:\n";
    printMatrix(A);

    cout << "\nMatrix B:\n";
    printMatrix(B);

    cout << "\nResultant Matrix C (A * B):\n";
    printMatrix(C);

    cout << "\nExecution time: " << duration.count() << " milliseconds\n";

    return 0;
}
