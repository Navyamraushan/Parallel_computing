#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

// Function to compute Fibonacci numbers
unsigned long long fibonacci(int n) {
    if (n <= 1)
        return n;
    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n = 1000000; // Modify this value for more Fibonacci numbers
    vector<unsigned long long> fib_series(n + 1);

    // Start timing the execution
    auto start = high_resolution_clock::now();

    // Parallel processing
    #pragma omp parallel for
    for (int i = 0; i <= n; ++i) {
        fib_series[i] = fibonacci(i);
    }

    // Stop timing the execution
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Print Fibonacci series
    cout << "Fibonacci series up to " << n << ":\n";
    for (int i = 0; i <= n; ++i) {
        cout << "Fib(" << i << ") = " << fib_series[i] << "\n";
    }

    // Print execution time
    cout << "Execution time: " << duration.count() << " milliseconds\n";

    return 0;
}
