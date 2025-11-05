#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define N 8
#define MAX_ITER 1
#define NUM_THREADS 2
#define EPSILON 1e-9

// Global data
double A[N][N];
double *B;
double *C;
double *tmp;
int num_threads = NUM_THREADS;
int bsize = N / NUM_THREADS;

// Thread function
void* matrix_mul(void *tn) {
	getchar();
    int tid = (int)(size_t)tn;
    for (int i = tid * bsize; i < (tid + 1) * bsize; i++) {
        double sum = 0.0;
        for (int k = 0; k < N; k++)
            sum += A[i][k] * B[k];
        C[i] = sum;
    }
    pthread_exit(NULL);
}

// Sequential version for verification
void sequential_compute(double A[N][N], double *B, double *C) {
    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int k = 0; k < N; k++)
            sum += A[i][k] * B[k];
        C[i] = sum;
    }
}

int main() {
    pthread_t *threads;
    threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    B = (double *)malloc(N * sizeof(double));
    C = (double *)malloc(N * sizeof(double));

    printf("pid: %d\n", getpid());

    srand(time(NULL));

    // ===== Initialize A and B randomly =====
    for (int i = 0; i < N; i++) {
        B[i] = ((double)rand() / RAND_MAX) * 10.0 - 5.0;  // [-5, 5]
        for (int j = 0; j < N; j++)
            A[i][j] = ((double)rand() / RAND_MAX) * 10.0 - 5.0;
    }

    // Keep a copy for verification
    double A_copy[N][N];
    double *B_ref = (double *)malloc(N * sizeof(double));
    double *C_ref = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        B_ref[i] = B[i];
        for (int j = 0; j < N; j++)
            A_copy[i][j] = A[i][j];
    }
	
    printf("Before computation.\n");
	getchar();

    // ===== Parallel computation =====
    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int tn = 0; tn < num_threads; tn++)
            pthread_create(&threads[tn], NULL, matrix_mul, (void *)(size_t)tn);

 
        for (int tn = 0; tn < num_threads; tn++)
            pthread_join(threads[tn], NULL);



        tmp = B;
        B = C;
        C = tmp;
    }


    // ===== Sequential verification =====
    for (int iter = 0; iter < MAX_ITER; iter++) {
        sequential_compute(A_copy, B_ref, C_ref);
        tmp = B_ref;
        B_ref = C_ref;
        C_ref = tmp;
    }

    // Compare
    int correct = 1;
    for (int i = 0; i < N; i++) {
        if (fabs(B[i] - B_ref[i]) > EPSILON) {
            printf("Mismatch at i=%d: parallel=%.6f, sequential=%.6f\n",
                   i, B[i], B_ref[i]);
            correct = 0;
        }
    }

    if (correct)
        printf("Verification passed! Parallel and sequential results match.\n");
    else
        printf("Verification failed.\n");

    printf("\nFinal B after %d iterations:\n", MAX_ITER);
    for (int i = 0; i < N; i++)
        printf("%8.4f ", B[i]);
    printf("\n");

    free(threads);
    free(B);
    free(C);
    free(B_ref);
    free(C_ref);
    return 0;
}
