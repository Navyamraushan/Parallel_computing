#include <iostream>
#include <mpi.h>
#include <bits/stdc++.h>
using namespace std;
// Amdahl's Law
double calculateSpeedup(double P, int N) {
    if (N <= 0) {
        std::cerr << "Number of processors must be greater than 0." << std::endl;
        return -1;
    }
    if (P < 0 || P > 1) {
        std::cerr << "Parallelizable portion P must be between 0 and 1." << std::endl;
        return -1;
    }
    return 1 / ((1 - P) + (P / N));
}

void sieveOfEratosthenes(int n) {
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int p = 2;
    while (p * p <= n) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                prime[i] = false;
            }
        }
        p++;
    }

    vector<int> primes;
    for (int p = 2; p <= n; ++p) {
        if (prime[p]) {
            primes.push_back(p);
        }
    }

    int numPrimes = primes.size();
    int localNumPrimes = numPrimes / size;
    int localPrimes[localNumPrimes];

    MPI_Scatter(primes.data(), localNumPrimes, MPI_INT, localPrimes, localNumPrimes, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < localNumPrimes; ++i) {
        cout << localPrimes[i] << " ";
    }
    cout << endl;
}

int main() {
    int n = 1000;

    MPI_Init(NULL, NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        auto start = chrono::high_resolution_clock::now();
        sieveOfEratosthenes(n);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Time taken: " << duration.count() << " seconds" << endl;
    } else {
        sieveOfEratosthenes(n);
    }

    MPI_Finalize();

    double P = 0.8; // Example parallelizable portion
    int N = 4;      // Example number of processors

    double speedup = calculateSpeedup(P, N);
    if (speedup != -1) {
        cout << "Speedup with P = " << P << " and N = " << N << " is: " << speedup << endl;
    }

    return 0;
}