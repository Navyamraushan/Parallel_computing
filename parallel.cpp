#include <iostream>
#include <omp.h>

int main() {
    // Parallel region with OpenMP
    #pragma omp parallel private(4)
    {
        // Get the thread ID
        int thread_id = omp_get_thread_num();
        
        // Print "Hello, World!" along with the thread ID
        std::cout << "Hello, World! from thread " << thread_id << std::endl;
    }

    return 0;
}
