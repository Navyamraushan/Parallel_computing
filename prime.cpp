#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to check if a number is prime
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    long long max_value;
    cout << "Enter the maximum value to check for primes: ";
    cin >> max_value;

    vector<long long> primes;

    // Start timing the execution
    auto start = high_resolution_clock::now();

    // Parallel processing to find prime numbers
    #pragma omp parallel for
    for (long long i = 2; i <= max_value; ++i) {
        if (isPrime(i)) {
            #pragma omp critical
            primes.push_back(i);
        }
    }

    // Stop timing the execution
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Print prime numbers
    cout << "Prime numbers up to " << max_value << ":\n";
    for (long long prime : primes) {
        cout << prime << " ";
    }
    cout << endl;

    // Print execution time
    cout << "Execution time: " << duration.count() << " milliseconds\n";

    return 0;
}
