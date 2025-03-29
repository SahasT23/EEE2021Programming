// Maybe add a Makefile if I have time

#ifndef GEMM_COMMON_H
#define GEMM_COMMON_H

#include <stdio.h>  
#include <stdlib.h>
#include <time.h>             // Packages added in for performance measurement
#include <sys/time.h>
#include <string.h>
#include <math.h>

typedef double var;

/**
 * Parameter defintions for clarity
 * @param m Number of rows in A and C
 * @param n Number of columns in B and C
 * @param k Number of columns in A / rows in B
 * @param A Pointer to matrix A (will be allocated)
 * @param B Pointer to matrix B (will be allocated)
 * @param C Pointer to matrix C (will be allocated)
 */

// Initialsing everything now, makes my life easier for the different ordering implemenmtations.

void initialise_matrices(int m, int n, int k, var **A, var **B, var **C) {
    *A = (var *)malloc(m * k * sizeof(var));
    *B = (var *)malloc(k * n * sizeof(var));
    *C = (var *)malloc(m * n * sizeof(var));
    
    if (*A == NULL || *B == NULL || *C == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    // A, B initialisation
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            (*A)[i*k + j] = (var)rand() / RAND_MAX;
        }
    }
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            (*B)[i*n + j] = (var)rand() / RAND_MAX;
        }
    }
    
    // C is initialised with zeros
    memset(*C, 0, m * n * sizeof(var));
}

/**
 * @param gemm_func Function pointer to the GeMM implementation
 * @param m Number of rows in A and C (for GeMM calculations)
 * @param n Number of columns in B and C (for GeMM calculations)
 * @param k Number of columns in A / rows in B
 * @param A Matrix A
 * @param B Matrix B
 * @param C Matrix C
 * @return Execution time in ms (milliseconds)
 */

double measure_time(void (*gemm_func)(int, int, int, var*, var*, var*), 
                   int m, int n, int k, var *A, var *B, var *C) {
    struct timeval start, end;
    
    // Reset matrix C to zeros afterwards
    memset(C, 0, m * n * sizeof(var));
    
    // Measure time
    gettimeofday(&start, NULL);
    gemm_func(m, n, k, A, B, C);
    gettimeofday(&end, NULL);
    
    // Calculate passed time in milliseconds
    double elapsed = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsed += (end.tv_usec - start.tv_usec) / 1000.0;
    
    return elapsed;
}

#endif // GEMM_COMMON_H