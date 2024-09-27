#include <iostream>
#include <omp.h>
using namespace std;

static long num_steps = 10;
double step;

// Reduction is used to combine the partial results of the threads, to avoid race conditions
int main() {
    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;

    #pragma omp parallel for reduction(+:sum) private(x)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    cout << "Value of Pi: " << pi << endl;
    return 0;
}