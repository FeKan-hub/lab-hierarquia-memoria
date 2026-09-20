#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    long N = atol(argv[1]);
    
    double *A = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i * N + j] = (double)(i + j); // Inicialização obrigatória

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    long pares = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((int)A[i * N + j] % 2 == 0) pares++;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf("[Varredura Linha] N: %ld | Pares: %ld | Tempo: %.4f s\n", N, pares, tempo);
    free(A);
    return 0;
}
