#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int sum = 0;

    #pragma omp parallel
    {
        #pragma omp critical
        {
            sum += 1;
            cout << "Thread " << omp_get_thread_num() << " incremented sum to " << sum << endl;
        }
    }

    std::cout << "Final sum: " << sum << std::endl;
    return 0;
}