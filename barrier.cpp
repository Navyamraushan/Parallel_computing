#include <iostream>
#include <omp.h>

int main() {
    const int num_threads = 4;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        std::cout << "Thread " << thread_id << " before the barrier.\n";

        // Explicit barrier synchronization
        #pragma omp barrier

        std::cout << "Thread " << thread_id << " after the barrier.\n";
    }

    return 0;
}