#include <mpi.h>
#include <iostream>
#include <chrono>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int data;
    if (world_rank == 0) {
        data = 100; // Root process initializes the data
        std::cout << "Process 0 broadcasting data: " << data << std::endl;
    }

    // Measure time for MPI_Bcast
    auto start_bcast = std::chrono::high_resolution_clock::now();
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    auto end_bcast = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_bcast = end_bcast - start_bcast;

    // All processes now have the broadcasted data
    std::cout << "Process " << world_rank << " received data via MPI_Bcast: " << data << std::endl;

    // Measure time for MPI_Send and MPI_Recv
    if (world_rank == 0) {
        auto start_send = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < world_size; i++) {
            MPI_Send(&data, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        auto end_send = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_send = end_send - start_send;
        std::cout << "Time taken for MPI_Send: " << elapsed_send.count() << " seconds" << std::endl;
    } else {
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Process " << world_rank << " received data via MPI_Send: " << data << std::endl;
    }

    if (world_rank == 0) {
        std::cout << "Time taken for MPI_Bcast: " << elapsed_bcast.count() << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}