#include <iostream>
#include <cstdlib>
#include <math.h>
#include <omp.h>

#define SIZE 50000
#define REAL 0
#define IMAG 1

int main() {
    auto a = new float[SIZE][2];
    auto b = new float[SIZE][2];
    auto c = new float[SIZE][2];
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

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            c[REAL][i] += (a[REAL][i] * b[REAL][j]) - (a[IMAG][i] * b[IMAG][j]);
            c[IMAG][i] += (a[IMAG][i] * b[REAL][j]) + (a[REAL][i] * b[IMAG][j]);
        }
    }

    t = omp_get_wtime() - t;

    printf("Time elapsed to execute program: %.2f seconds\n", t);
}
