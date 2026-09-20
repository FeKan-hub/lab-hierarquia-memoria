#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char* argv[]) {
    if (argc != 3) return 1;
    long N = atol(argv[1]);
    int B_SIZE = atoi(argv[2]);

    double *A = malloc(N * N * sizeof(double));
    double *B = malloc(N * N * sizeof(double));
    double *C = calloc(N * N, sizeof(double));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int i_b = 0; i_b < N; i_b += B_SIZE) {
        for (int j_b = 0; j_b < N; j_b += B_SIZE) {
            for (int k_b = 0; k_b < N; k_b += B_SIZE) {
                for (int i = i_b; i < MIN(i_b + B_SIZE, N); ++i) {
                    for (int k = k_b; k < MIN(k_b + B_SIZE, N); ++k) {
                        double a_ik = A[i * N + k];
                        for (int j = j_b; j < MIN(j_b + B_SIZE, N); ++j) {
                            C[i * N + j] += a_ik * B[k * N + j];
                        }
                    }
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf("[Matmul Bloco] N: %ld | Bloco: %d | Tempo: %.4f s\n", N, B_SIZE, tempo);
    free(A); free(B); free(C);
    return 0;
}
