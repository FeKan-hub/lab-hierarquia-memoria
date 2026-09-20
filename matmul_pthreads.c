#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long N;
int num_threads;
double *A, *B, *C;

void* matmul_worker(void* arg) {
    long id = (long)arg;
    long linhas_por_thread = N / num_threads;
    long inicio = id * linhas_por_thread;
    long fim = (id == num_threads - 1) ? N : inicio + linhas_por_thread;

    for (long i = inicio; i < fim; ++i) {
        for (long j = 0; j < N; ++j) {
            double sum = 0.0;
            for (long k = 0; k < N; ++k) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) return 1;
    N = atol(argv[1]);
    num_threads = atoi(argv[2]);

    A = malloc(N * N * sizeof(double));
    B = malloc(N * N * sizeof(double));
    C = calloc(N * N, sizeof(double));

    for (long i = 0; i < N; i++)
        for (long j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }

    pthread_t threads[num_threads];
    struct timespec inicio_t, fim_t;
    clock_gettime(CLOCK_MONOTONIC, &inicio_t);

    for (long i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, matmul_worker, (void*)i);

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &fim_t);
    double tempo = (fim_t.tv_sec - inicio_t.tv_sec) + (fim_t.tv_nsec - inicio_t.tv_nsec) / 1e9;
    
    printf("[Matmul Pthreads] N: %ld | Threads: %d | Tempo: %.4f s\n", N, num_threads, tempo);
    free(A); free(B); free(C);
    return 0;
}
