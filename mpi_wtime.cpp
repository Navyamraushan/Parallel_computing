#include <mpi.h>
#include <iostream>

// Function to compute Fibonacci number
int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 30; // Example Fibonacci number to compute
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    double start_time = MPI_Wtime();
    int result = fib(n);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        std::cout << "Fibonacci number " << n << " is " << result << std::endl;
        std::cout << "Execution time: " << end_time - start_time << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}