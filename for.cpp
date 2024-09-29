// implemention of open mp for

#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    // Parallel region with OpenMP
    #pragma omp parallel
    {
        // Get the thread ID
        
        
        #pragma omp for
        
        for (int i = 0; i < 10; i++)
        {
            int thread_id = omp_get_thread_num();
            // Print "Hello, World!" along with the thread ID
            cout << "Hello, World! from thread " << thread_id << " i = " << i << endl;
        }
        
    }

    return 0;
}