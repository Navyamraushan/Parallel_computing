// #include <omp.h>
// #include <iostream>
// using namespace std;


// int main(int argc, char *argv[]) {

//     #pragma omp parallel num_threads(4)
//     {
//         #pragma omp single
//         {
//             int thread_id = omp_get_thread_num();
//             cout << "This is a single thread printed by " << thread_id << endl;
//         }

//         # pragma omp master
//         {
//             int thread_id = omp_get_thread_num();
//             cout << "This is a master thread printed by " << thread_id << endl;
//         }

//         int thread_id = omp_get_thread_num();
//         cout << "This is a parallel region printed by " << thread_id << endl;
//     } /* end of parallel region */

    
// }
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            int thread_id = omp_get_thread_num();
            printf("This is a single thread printed by %d\n", thread_id);
        }

        #pragma omp master
        {
            int thread_id = omp_get_thread_num();
            printf("This is a master thread printed by %d\n", thread_id);
        }

        int thread_id = omp_get_thread_num();
        printf("This is a parallel region printed by %d\n", thread_id);
    } /* end of parallel region */

    return 0;
}