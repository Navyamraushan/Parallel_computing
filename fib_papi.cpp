#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>
#include <papi.h>  // Include PAPI header

// g++ -fopenmp -o fib_papi fib_papi.cp -lpapi

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
    int n = 40; // Modify this value for more Fibonacci numbers
    vector<unsigned long long> fib_series(n + 1);

    // Initialize PAPI library and create an event set
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        cerr << "PAPI library initialization error!" << endl;
        return -1;
    }

    int event_set = PAPI_NULL;  // Event set to hold the counters
    long long values[3] = {0, 0, 0};  // Array to store PAPI results

    // Create the event set
    if (PAPI_create_eventset(&event_set) != PAPI_OK) {
        cerr << "PAPI failed to create an event set!" << endl;
        return -1;
    }

    // Add events to monitor: FLOPs, total instructions, cache misses
    if (PAPI_add_event(event_set, PAPI_FP_OPS) != PAPI_OK ||
        PAPI_add_event(event_set, PAPI_TOT_INS) != PAPI_OK ||
        PAPI_add_event(event_set, PAPI_L1_DCM) != PAPI_OK) {
        cerr << "PAPI failed to add events!" << endl;
        return -1;
    }

    // Start counting the events in the event set
    if (PAPI_start(event_set) != PAPI_OK) {
        cerr << "PAPI failed to start counters!" << endl;
        return -1;
    }

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

    // Stop counting the events in the event set
    if (PAPI_stop(event_set, values) != PAPI_OK) {
        cerr << "PAPI failed to stop counters!" << endl;
        return -1;
    }

    // Clean up the event set
    PAPI_cleanup_eventset(event_set);
    PAPI_destroy_eventset(&event_set);
    PAPI_shutdown();

    // Print Fibonacci series (optional, can be commented out for large n)
    cout << "Fibonacci series up to " << n << ":\n";
    for (int i = 0; i <= n; ++i) {
        cout << "Fib(" << i << ") = " << fib_series[i] << "\n";
    }

    // Print execution time
    cout << "Execution time: " << duration.count() << " milliseconds\n";

    // Print PAPI results
    cout << "FLOPs: " << values[0] << endl;
    cout << "Total Instructions: " << values[1] << endl;
    cout << "L1 Cache Misses: " << values[2] << endl;

    return 0;
}
