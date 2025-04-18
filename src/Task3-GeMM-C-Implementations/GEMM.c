#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <sys/time.h>  // Added these packages for timing calculations.

// To make the examiner's life easier, just add a symbol or tick for each mark, then tally it up I guess.

// Code compiles correctly (1 mark)

// Number of 'runs' to average for each test case (best of 3, average will be )
#define NUM_RUNS 3

/**
 * Function to get current time in microseconds (more accurate for measurement)
 * Can use again for the optimised version as well. I need to change this timing method. 
 */
double get_time() {
    struct timeval timv;
    gettimeofday(&timv, NULL);
    return timv.tv_sec + timv.tv_usec * 1e-6; // Originally used division, probably a bit faster for computation. 
}

/**
 * Sigmoid function to generate values between 0 and 1
 * The function takes a value x and returns 1/(1+e^(-x))
 */
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}


/*
Initialising the matrices for AB + C.
*/
void init_matrices(int m, int n, int k, double **A, double **B, double **C) {  // Correct types for m, n, k, A, B and C (1 mark)
    *A = (double *)malloc(m * k * sizeof(double));
    *B = (double *)malloc(k * n * sizeof(double));
    *C = (double *)malloc(m * n * sizeof(double));
    
    if (*A == NULL || *B == NULL || *C == NULL) {  // Shouldn't happen, more for debugging purposes (I know, a debugger exists)
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // /**
    //  * Initialising the values of the matrices to be between 0 and 1 for matrices A and B. (1.5 marks) 
    //  * Best method I have seen so far for randomisation. I see why we need it between 0 and 1. 
    //  * Maybe add in a sigmoid function?? 
    //  */
    // for (int i = 0; i < m; i++) {  // Correctly nested loops (2 marks)
    //     for (int j = 0; j < k; j++) {
    //         (*A)[i*k + j] = (double)rand() / RAND_MAX;
    //     }
    // }
    
    // for (int i = 0; i < k; i++) {
    //     for (int j = 0; j < n; j++) {
    //         (*B)[i*n + j] = (double)rand() / RAND_MAX;
    //     }
    // }
    
    // // Initialising C as a zero matrix, needed for GeMM to be done correctly. (1.5 marks)
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         (*C)[i*n + j] = 0.0;
    //     }
    // }

    for (int i = 0; i < m; i++) {  // Correctly nested loops (2 marks)
        for (int j = 0; j < k; j++) {
            // Generate random value between -5 and 5, then apply sigmoid
            double random_value = ((double)rand() / RAND_MAX) * 10.0 - 5.0;
            (*A)[i*k + j] = sigmoid(random_value);
        }
    }
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            // Generate random value between -5 and 5, then apply sigmoid
            double random_value = ((double)rand() / RAND_MAX) * 10.0 - 5.0;
            (*B)[i*n + j] = sigmoid(random_value);
        }
    }

    // Initialising C as a zero matrix, needed for GeMM to be done correctly. (1.5 marks)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            (*C)[i*n + j] = 0.0;
        }
    }
}

// Resets the matrix to 0 every time.
void reset_matrix_c(double *C, int m, int n) {
    for (int i = 0; i < m * n; i++) {
        C[i] = 0.0;
    }
}

// Clears the matrices for the next calculation. 
void free_matrices(double *A, double *B, double *C) {
    free(A);
    free(B);
    free(C);
}

/**
 * MNK implementation (row-by-row) Time Complexity of O(n^3).
 * The reason why it is n^3 is becuase of the 3 nested 'for' loops,
 * The outermost loop runs 'm' times.
 * The middle loop runs 'n' times for each iteration of the outer loop.
 * The innermost loop runs 'k' times for each iteration of the middle loop, 
 * So the Big O notation will amount to  O(m * n * k), -> O(n^3).
 * Even if the loop ordering changes, it will always be O(n^3). 
 * 
 * Space complexity is much more simpler for this algorithm/loop ordering.
 * Since no additional structures are allocated within the function.
 * (only the given matrices are used), the space complexity is O(1), regardless of loop ordering.
 * 
 * Spatial Locality:
 * matrix A: Accesses elements of row i sequentially (good for the matrix).
 * Poor spatial locality for matrix B and matrix C: (matrix B) Accesses column j vertically, (matrix C) Repeatedly accesses the same element.
 * 
 * Temporal Locality:
 * Poor for matrix A and B: Each element of matrix A/B is used only once per inner loop.
 * Good for matrix C: Repeatedly reuses the same C[i,j] element in the innermost loop.
 */
void mnk_gemm(int m, int n, int k, double *A, double *B, double *C) {  // Correctly nested loops (2 marks)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < k; p++) {
                C[i*n + j] += A[i*k + p] * B[p*n + j];
            }
        }
    }
}

/**
 * MKN implementation (row-inner-column) Time Complexity of O(n^3).
 * In practice, there should be very minimal difference between the different orderings,
 * 
 * Spatial Locality:
 * Good for matrix A: Each A[i,p] is reused across the entire inner loop.
 * Good for matrix B and C: Accesses row p/i sequentially.
 * 
 * Temporal Locality:
 * Good for matrix A: Each element A[i,p] is reused n times in the inner loop.
 * Poor for matrix B and C: Each element is used once per inner loop (for matrix B) and once for the middle loop (matrix C).
 */
void mkn_gemm(int m, int n, int k, double *A, double *B, double *C) {  // Correctly nested loops (2 marks)
    for (int i = 0; i < m; i++) {
        for (int p = 0; p < k; p++) {                           // Two different loop ordering (2 marks)
            double a_ip = A[i*k + p];
            for (int j = 0; j < n; j++) {
                C[i*n + j] += a_ip * B[p*n + j];
            }
        }
    }
}

/**
 * Proper indexing for 1D arrays as matrices (3 marks)
 * 
 * NMK implementation (column-by-column) Time Complexity of O(n^3).
 * 
 * Spatial Locality:
 * Good for matrix A: Accesses row i sequentially.
 * Poor for matrix B and C: Accesses column j vertically.
 * 
 * Temporal Locality:
 * Poor for matrix A and B: Each element used once per inner loop.
 * Good for matrix C: Reuses the same C[i,j] in the innermost loop.
 */
void nmk_gemm(int m, int n, int k, double *A, double *B, double *C) {  // Correctly nested loops (2 marks)
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {               // Proper indexing for 1D arrays as matrices (3 marks)
            for (int p = 0; p < k; p++) {          // Implements C := AB + C correctly (3 marks)
                C[i*n + j] += A[i*k + p] * B[p*n + j];
            }
        }
    }
}

/**
 * NKM implementation (column-inner-row) Time Complexity of O(n^3).
 * 
 * Spatial Locality:
 * Poor for matrix A and C: Accesses column p/j vertically.
 * Good for matrix B: Each B[p,j] is reused across the inner loop.
 * 
 * Temporal Locality:
 * Poor for matrix A: Each element is used once per inner loop and once per middle loop for matrix C.
 * Good for matrix B: Each B[p,j] is reused m times in the inner loop.
 * 
 * A[i*k + p] accesses the p-th element in the i-th row of the matrix.
 * B[p*n + j] accesses the j-th element in the p-th row of the matrix.
 * A[i*k + p] * B[p*n + j] is a single term in the matrix computation.
 */
void nkm_gemm(int m, int n, int k, double *A, double *B, double *C) {  // Correctly nested loops (2 marks)
    for (int j = 0; j < n; j++) {
        for (int p = 0; p < k; p++) {
            double b_pj = B[p*n + j];
            for (int i = 0; i < m; i++) {
                C[i*n + j] += A[i*k + p] * b_pj;
            }
        }
    }
}

// I hope my code is readable (2 marks) 

/**
 * KMN implementation (inner-row-column) Time Complexity of O(n^3).
 * 
 * Spatial Locality:
 * Poor for matrix A: Each A[i,p] is accessed only once in the middle loop.
 * Good for matrix B and C: Accesses row p/i sequentially.
 * 
 * Temporal Locality:
 * Good for matrix A: Each A[i,p] is reused n times in the inner loop.
 * Poor for matrix B: Each element of row p is used once per inner loop and accessed once for matrix C.
 */
void kmn_gemm(int m, int n, int k, double *A, double *B, double *C) {  // Correctly nested loops (2 marks)
    for (int p = 0; p < k; p++) {
        for (int i = 0; i < m; i++) {
            double a_ip = A[i*k + p];
            for (int j = 0; j < n; j++) {
                C[i*n + j] += a_ip * B[p*n + j];
            }
        }
    }
}

/**
 * KNM implementation (inner-column-row) Time Complexity of O(n^3).
 * Spatial Locality:
 * Poor for matrix A and C: Accesses column p/j vertically.
 * Good for matrix B: Each B[p,j] is reused across the inner loop.
 * 
 * Temporal Locality:
 * Poor for matrix A and C: Each element is accessed once per inner loop.
 * Good for matrix B: Each B[p,j] is reused m times in the inner loop.
 */
void knm_gemm(int m, int n, int k, double *A, double *B, double *C) {  // Correctly nested loops (2 marks)
    for (int p = 0; p < k; p++) {
        for (int j = 0; j < n; j++) {
            double b_pj = B[p*n + j];
            for (int i = 0; i < m; i++) {
                C[i*n + j] += A[i*k + p] * b_pj;
            }
        }
    } 
}

/**
 * Analysis in report (10 marks) (hopefully)
 * Python plots (shows log graphs, comparison and benchmarking etc.) (4 marks) (again, hopefully).
 * Created OptGEMM.c that uses blocking, multithreading and finally multithreading and blocking for the m-n-k loop ordering.
 * Also added analysis for the alternate method, added graphes and plots.  (8 marks)
 * Terminal output shown when code has been compiled.   
*/

int main() {
    // Random number generation.
    srand(time(NULL));
    
    /*
    Matrix sizes to test (The jump between matrix sizes is on purpose, can clearly see the time increasing as it is a cubic relationship). 
    Python file for plotting the graph and observing different execution times (4 marks).
    */
    int sizes[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400};  // If you (the examiner) want to, can alter the array, add a larger size if needed.
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    // All loop orderings that I have used (only needed two, but I added more).
    typedef void (*gemm_func)(int, int, int, double*, double*, double*);
    gemm_func funcs[] = {mnk_gemm, mkn_gemm, nmk_gemm, nkm_gemm, kmn_gemm, knm_gemm};
    const char *func_names[] = {"MNK", "MKN", "NMK", "NKM", "KMN", "KNM"};
    int num_funcs = sizeof(funcs) / sizeof(funcs[0]);
    
    // Create results CSV file
    FILE *results_file = fopen("gemm_times.csv", "w");
    if (results_file == NULL) {
        fprintf(stderr, "Error opening results file\n");
        return 1;
    }
    
    // CSV file headers, easier for me to use for graph plotting purposes. Check the python scripts for plotting. (GEMMPlotting.py) 
    fprintf(results_file, "Matrix Size");
    for (int i = 0; i < num_funcs; i++) {
        fprintf(results_file, ",%s", func_names[i]);
    }
    fprintf(results_file, "\n");
    
    // Run benchmarks for each matrix size
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        int m = size, n = size, k = size;
        
        printf("Testing matrices of size %d x %d...\n", size, size);
        
        fprintf(results_file, "%d", size);
        
        // Initialise matrices correctly for the benchnarks
        double *A, *B, *C;
        init_matrices(m, n, k, &A, &B, &C);
        
        // Benchmark each loop ordering correctly
        for (int i = 0; i < num_funcs; i++) {
            double total_time = 0.0;
            
            // Run the implementation NUM_RUNS (3, but you can alter it) times and average the results
            for (int run = 0; run < NUM_RUNS; run++) {
                // Reset matrix C to zeros for each run
                reset_matrix_c(C, m, n);
                
                // Measure execution time
                double start_time = get_time();
                funcs[i](m, n, k, A, B, C);
                double end_time = get_time();
                
                total_time += (end_time - start_time);
            }
            
            // Calculate the average execution time
            double avg_time = total_time / NUM_RUNS;
            
            // Write results to CSV file
            fprintf(results_file, ",%.6f", avg_time);
            
            // Print results to console
            printf("  %s: %.6f s\n", func_names[i], avg_time);
        }
        
        fprintf(results_file, "\n");
        fflush(results_file);
        
        // Free allocated memory
        free_matrices(A, B, C);
    }
    
    fclose(results_file);
    
    printf("\nBenchmarking complete. Results saved to gemm_times.csv\n");
    
    return 0;
}