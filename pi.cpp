/**
 * @file pi.cpp
 * @brief This program calculates the value of Pi using numerical integration and parallel computing with OpenMP.
 *
 * The program divides the task of calculating Pi into multiple threads to speed up the computation.
 * It uses the midpoint rule for numerical integration to approximate the value of Pi.
 *
 * The main steps are:
 * 1. Define the number of steps for the integration.
 * 2. Calculate the width of each step.
 * 3. Use OpenMP to parallelize the summation of the areas of rectangles under the curve.
 * 4. Each thread calculates a partial sum of the areas.
 * 5. The partial sums are combined using an atomic operation to avoid race conditions.
 * 6. The final value of Pi is printed with a precision of 10 decimal places.
 *
 * @note The number of steps is set to 1,000,000,000 for a high-precision calculation.
 * @note The OpenMP directives are used to parallelize the for loop and to ensure atomic updates to the shared variable `pi`.
 */
#include <iostream>
#include <omp.h>
#include <iomanip>
using namespace std;



int main() {
    const long num_steps = 1000000000;
    double step = 1.0 / static_cast<double>(num_steps);
    double pi = 0.0;

    #pragma omp parallel
    {
        double sum = 0.0;
        #pragma omp for
        for (long i = 0; i < num_steps; ++i) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        pi += sum * step;
    }

    cout << std::fixed << std::setprecision(10) << "Calculated Pi: " << pi << endl;
    return 0;
}