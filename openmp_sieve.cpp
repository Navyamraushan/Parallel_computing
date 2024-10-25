#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
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

    int p = 2;
    while (p * p <= n) {
        if (prime[p]) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = p * p; i <= n; i += p) {
                prime[i] = false;
            }
        }
        p++;
    }

    for (int p = 2; p <= n; ++p) {
        if (prime[p]) {
            cout << p << " ";
        }
    }
    cout << endl;
}


int main() {
    int n = 1000;
    
    auto start = chrono::high_resolution_clock::now();
    sieveOfEratosthenes(n);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double> duration = end - start;

    double P = 0.8; // Example parallelizable portion
    int N = 4;

    double speedup = calculateSpeedup(P, N);
    if (speedup != -1) {
        cout << "Speedup with P = " << P << " and N = " << N << " is: " << speedup << endl;
    }

    cout << "Time taken: " << duration.count() << " seconds" << endl;
    
    return 0;
}

