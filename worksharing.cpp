#include <omp.h>
#include <iostream>
using namespace std;
#define N 1000

int main(int argc, char *argv[]) {

    int i;
    float a[N], b[N], c[N], d[N];

    /* Some initializations */
    for (i = 0; i < N; i++) {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
    }

    #pragma omp parallel shared(a,b,c,d) private(i)
    {
        #pragma omp sections nowait
        {
            #pragma omp section
            {
                int thread_id = omp_get_thread_num();
                cout << "Thread " << thread_id << " is executing the first section (c[i] = a[i] * b[i])" << std::endl;
                for (i = 0; i < N; i++)
                    c[i] = a[i] * b[i];
            }

            #pragma omp section
            {
                int thread_id = omp_get_thread_num();
                cout << "Thread " << thread_id << " is executing the second section (d[i] = a[i] + b[i])" << std::endl;
                for (i = 0; i < N; i++)
                    d[i] = a[i] + b[i];
            }
            
        } /* end of sections */
    } /* end of parallel region */

    
}
