#include <omp.h>
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
            int num_threads_1 = omp_get_thread_num();
            for (i = 0; i < N; i++)
                c[i] = a[i] * b[i];
            printf("%d", num_threads_1);

            #pragma omp section
            int num_threads_1 = omp_get_thread_num();
            for (i = 0; i < N; i++)
                d[i] = a[i] + b[i];
            
            printf("%d", num_threads_1);

        } /* end of sections */
    } /* end of parallel region */

    return 0;
}
