#include <mpi.h>
#include <iostream>
#include <vector>
using namespace std;

void calculate_fibonacci(int n, std::vector<long long>& fib) {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < n; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    // int rank, size;
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // MPI_Comm_size(MPI_COMM_WORLD, &size);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int n = 10; // Change this to the desired number of Fibonacci terms
    vector<long long> fib(n);

    // if (world_rank == 0) {
    //     calculate_fibonacci(n, fib);
    //     for (int i = 0; i < n; ++i) {
    //         cout << "Fib(" << i << ") = " << fib[i] << " From process " 
    //         << world_rank << endl;
    //     }
    // }

     calculate_fibonacci(n, fib);
        for (int i = 0; i < n; ++i) {
            cout << "Fib(" << i << ") = " << fib[i] << " From process " 
            << world_rank << endl;
        }

    MPI_Finalize();
    return 0;
}