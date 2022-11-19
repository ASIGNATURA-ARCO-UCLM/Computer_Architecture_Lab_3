#include <iostream>
#include <cstdlib>
#include <math.h>
#include <omp.h>

#define SIZE 50000
#define REAL 0
#define IMAG 1


int main() {
    float aReal[SIZE];
    float aImag[SIZE];
    float bReal[SIZE];
    float bImag[SIZE];
    auto c = new float[SIZE][2];
    double n = SIZE;
    double seed = 3.141592653589793;

    // Generate pseudo random numbers
    for(int i = 0; i < SIZE; i++) {
        aReal[i] = sin((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        aImag[i] = cos((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        bReal[i] = sin((6*seed*i * ( seed*i - 1) + 1));
        bImag[i] = cos((6*seed*i * ( seed*i - 1) + 1));
    }

    double t = omp_get_wtime();

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            c[i][REAL] += (aReal[i] * bReal[j]) - (aImag[i] * bImag[j]);
            c[i][IMAG] += (aReal[i] * bReal[j]) + (aReal[i] * bImag[j]);
        }
    }

    t = omp_get_wtime() - t;

    printf("Time elapsed to execute program: %.2f seconds\n", t);
}