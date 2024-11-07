#include<mpi.h>
#include <iostream>
#include <vector>

using namespace std;

void matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B, 
                    vector<vector<int>>& C, int startRow, int endRow) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
    
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < p; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 40; // Example size, can be changed
    vector<vector<int>> A(n, vector<int>(n, 1)); // Example matrix A
    vector<vector<int>> B(n, vector<int>(n, 1)); // Example matrix B
    vector<vector<int>> C(n, vector<int>(n, 0)); // Result matrix C

    int rowsPerProcess = n / size;
    int startRow = rank * rowsPerProcess;
    int endRow = (rank == size - 1) ? n : startRow + rowsPerProcess;

    matrixMultiply(A, B, C, startRow, endRow);

    if (rank != 0) {
        for (int i = startRow; i < endRow; ++i) {
            MPI_Send(C[i].data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    } else {

        cout << "Executed by process " << rank << endl;
        cout << "Size of Matrix is " << n << endl;
        for (int i = 1; i < size; ++i) {
            int start = i * rowsPerProcess;
            int end = (i == size - 1) ? n : start + rowsPerProcess;
            for (int j = start; j < end; ++j) {
                MPI_Recv(C[j].data(), n, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        // Print result matrix C
        for (const auto& row : C) {
            for (const auto& elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
    return 0;
}
// to ruln this file
// mpic++ papi_openmp.cpp -o mcpp -lpapi -I/home/adityasr/Desktop/papi-7.2.0b1/src/bin/include
// mpirun -np 4 ./mcpp
