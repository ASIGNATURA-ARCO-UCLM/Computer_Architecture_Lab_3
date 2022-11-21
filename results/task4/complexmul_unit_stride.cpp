 #include <iostream>
#include <cstdlib>
#include <math.h>
#include <omp.h>
#include "advisor-annotate.h"

#define SIZE 50000
#define REAL 0
#define IMAG 1

int main() {
    auto a = new float[2][SIZE];
    auto b = new float[2][SIZE];
    auto c = new float[2][SIZE];
    double n = SIZE;
    double seed = 3.141592653589793;

    // Generate pseudo random numbers
    for(int i = 0; i < SIZE; i++) {
        a[REAL][i] = sin((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        a[IMAG][i] = cos((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        b[REAL][i] = sin((6*seed*i * ( seed*i - 1) + 1));
        b[IMAG][i] = cos((6*seed*i * ( seed*i - 1) + 1));
    }

    double t = omp_get_wtime();

    ANNOTATE_SITE_BEGIN(bucleExterior);
    for(int i = 0; i < SIZE; i++) {
        ANNOTATE_ITERATION_TASK();
        ANNOTATE_SITE_BEGIN(bucleInterior);
        for(int j = 0; j < SIZE; j++) {
            ANNOTATE_ITERATION_TASK();
            c[REAL][i] += (a[REAL][i] * b[REAL][j]) - (a[IMAG][i] * b[IMAG][j]);
            c[IMAG][i] += (a[IMAG][i] * b[REAL][j]) + (a[REAL][i] * b[IMAG][j]);
        }
        ANNOTATE_SITE_END();
    }
    ANNOTATE_SITE_END();

    t = omp_get_wtime() - t;

    printf("Time elapsed to execute program: %.2f seconds\n", t);
}
