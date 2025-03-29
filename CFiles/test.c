#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

// Function to get current time in microseconds
double get_time_usec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec * 1000000 + (double)tv.tv_usec;
}

// Function to initialize matrices with random values
void initialize_matrices(double **A, double **B, double **C, int m, int n, int k) {
    // Initialize random number generator
    srand(time(NULL));
    
    // Initialize matrix A with random values between 0 and 1
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }
    
    // Initialize matrix B with random values between 0 and 1
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = (double)rand() / RAND_MAX;
        }
    }
    
    // Initialize matrix C as all zeros
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
        }
    }
}

// Function to allocate memory for matrices
void allocate_matrices(double ***A, double ***B, double ***C, int m, int n, int k) {
    // Allocate memory for matrix A (m x k)
    *A = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        (*A)[i] = (double *)malloc(k * sizeof(double));
    }
    
    // Allocate memory for matrix B (k x n)
    *B = (double **)malloc(k * sizeof(double *));
    for (int i = 0; i < k; i++) {
        (*B)[i] = (double *)malloc(n * sizeof(double));
    }
    
    // Allocate memory for matrix C (m x n)
    *C = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        (*C)[i] = (double *)malloc(n * sizeof(double));
    }
}

// Function to free memory allocated for matrices
void free_matrices(double **A, double **B, double **C, int m, int k) {
    // Free memory for matrix A
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    
    // Free memory for matrix B
    for (int i = 0; i < k; i++) {
        free(B[i]);
    }
    free(B);
    
    // Free memory for matrix C
    for (int i = 0; i < m; i++) {
        free(C[i]);
    }
    free(C);
}

// Standard GEMM implementation: C := AB + C
void mnk_gemm(var m, var n, var k, var **A, var **B, var **C) {
    // Implementation follows the formula C[i][j] += A[i][p] * B[p][j]
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < k; p++) {
                C[i][j] += A[i][p] * B[p][j];
            }
        }
    }
}

// Alternative loop order: nmk
void nmk_gemm(int m, int n, int k, double **A, double **B, double **C) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            for (int p = 0; p < k; p++) {
                C[i][j] += A[i][p] * B[p][j];
            }
        }
    }
}

// Alternative loop order: kmn
void kmn_gemm(int m, int n, int k, double **A, double **B, double **C) {
    for (int p = 0; p < k; p++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][p] * B[p][j];
            }
        }
    }
}

// Calculate memory usage in bytes
size_t calculate_memory_usage(int m, int n, int k) {
    size_t bytes = 0;
    
    // Memory for matrix A (m x k)
    bytes += m * k * sizeof(double);
    bytes += m * sizeof(double*);
    
    // Memory for matrix B (k x n)
    bytes += k * n * sizeof(double);
    bytes += k * sizeof(double*);
    
    // Memory for matrix C (m x n)
    bytes += m * n * sizeof(double);
    bytes += m * sizeof(double*);
    
    return bytes;
}

// Function to run benchmarks with different loop orders
void run_benchmark(int m, int n, int k) {
    double **A, **B, **C;
    double start_time, end_time, execution_time;
    size_t memory_usage;
    
    printf("Matrix dimensions: m=%d, n=%d, k=%d\n", m, n, k);
    
    // Calculate memory usage
    memory_usage = calculate_memory_usage(m, n, k);
    printf("Estimated memory usage: %.2f MB\n", (double)memory_usage / (1024 * 1024));
    
    // Allocate and initialize matrices
    allocate_matrices(&A, &B, &C, m, n, k);
    initialize_matrices(A, B, C, m, n, k);
    
    // Benchmark mnk loop order (standard)
    start_time = get_time_usec();
    mnk_gemm(m, n, k, A, B, C);
    end_time = get_time_usec();
    execution_time = (end_time - start_time) / 1000.0;  // Convert to milliseconds
    printf("MNK loop order execution time: %.2f ms\n", execution_time);
    
    // Reset matrix C
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
        }
    }
    
    // Benchmark nmk loop order
    start_time = get_time_usec();
    nmk_gemm(m, n, k, A, B, C);
    end_time = get_time_usec();
    execution_time = (end_time - start_time) / 1000.0;  // Convert to milliseconds
    printf("NMK loop order execution time: %.2f ms\n", execution_time);
    
    // Reset matrix C
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
        }
    }
    
    // Benchmark kmn loop order
    start_time = get_time_usec();
    kmn_gemm(m, n, k, A, B, C);
    end_time = get_time_usec();
    execution_time = (end_time - start_time) / 1000.0;  // Convert to milliseconds
    printf("KMN loop order execution time: %.2f ms\n", execution_time);
    
    // Free allocated memory
    free_matrices(A, B, C, m, k);
    
    printf("\n");
}

int main() {
    printf("General Matrix Multiplication (GEMM) Benchmark\n");
    printf("---------------------------------------------\n\n");
    
    // Test with small matrices
    run_benchmark(100, 100, 100);
    
    // Test with medium matrices
    run_benchmark(500, 500, 500);
    
    // Test with larger matrices
    run_benchmark(1000, 1000, 1000);
    
    // Test with non-square matrices
    run_benchmark(2000, 1000, 500);
    
    // Allow user to specify custom dimensions
    int m, n, k;
    printf("Enter custom matrix dimensions (m n k): ");
    scanf("%d %d %d", &m, &n, &k);
    run_benchmark(m, n, k);
    
    return 0;
}