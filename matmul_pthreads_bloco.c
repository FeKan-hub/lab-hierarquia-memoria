#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

long N;
int num_threads, B_SIZE;
double *A, *B, *C;

void* matmul_bloco_worker(void* arg) {
    long id = (long)arg;
    long linhas_por_thread = N / num_threads;
    long inicio_linha = id * linhas_por_thread;
    long fim_linha = (id == num_threads - 1) ? N : inicio_linha + linhas_por_thread;

    for (long i_b = inicio_linha; i_b < fim_linha; i_b += B_SIZE) {
        for (long j_b = 0; j_b < N; j_b += B_SIZE) {
            for (long k_b = 0; k_b < N; k_b += B_SIZE) {
                for (long i = i_b; i < MIN(i_b + B_SIZE, fim_linha); ++i) {
                    for (long k = k_b; k < MIN(k_b + B_SIZE, N); ++k) {
                        double a_ik = A[i * N + k];
                        for (long j = j_b; j < MIN(j_b + B_SIZE, N); ++j) {
                            C[i * N + j] += a_ik * B[k * N + j];
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 4) return 1;
    N = atol(argv[1]);
    B_SIZE = atoi(argv[2]);
    num_threads = atoi(argv[3]);

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
        pthread_create(&threads[i], NULL, matmul_bloco_worker, (void*)i);

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &fim_t);
    double tempo = (fim_t.tv_sec - inicio_t.tv_sec) + (fim_t.tv_nsec - inicio_t.tv_nsec) / 1e9;
    
    printf("[Matmul Pthreads Bloco] N: %ld | Bloco: %d | Threads: %d | Tempo: %.4f s\n", N, B_SIZE, num_threads, tempo);
    free(A); free(B); free(C);
    return 0;
}
