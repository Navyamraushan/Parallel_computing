#include <iostream>
#include <vector>
#include <cstdlib>
#include <mpi.h>

#define N 100 // Array size
#define MASTER 0

// Function to perform bubble sort on an array segment
void bubble_sort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    std::vector<int> data(N);
    std::vector<int> local_data(N);
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = N / size;

    // Master initializes the array
    if (rank == MASTER) {
        std::cout << "Original Array:" << std::endl;
        for (int i = 0; i < N; i++) {
            data[i] = rand() % 1000; // Random numbers between 0 and 999
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Scatter the data to each process
    MPI_Scatter(data.data(), chunk_size, MPI_INT, local_data.data(), chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

    // Each process sorts its local chunk
    local_data.resize(chunk_size); // Resize to the appropriate chunk size
    bubble_sort(local_data);

    // Gather sorted chunks back to master process
    MPI_Gather(local_data.data(), chunk_size, MPI_INT, data.data(), chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

    // Master performs a final merge of sorted subarrays
    if (rank == MASTER) {
        bubble_sort(data);
        std::cout << "Sorted Array:" << std::endl;
        for (int i = 0; i < N; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
// to rum this
// mpic++ -o bubble_sort bubble_sort.cpp
// mpirun -np 4 ./bubblesort.cpp
