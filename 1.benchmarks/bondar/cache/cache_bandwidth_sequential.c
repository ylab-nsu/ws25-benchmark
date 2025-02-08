#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void measure_read_bandwidth(size_t N, size_t K, int *a) {
    volatile long sink = 0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t t = 0; t < K; t++) {
        for (size_t i = 0; i < N; i++) {
            sink = a[i]; 
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Read-Bandwidth: ");
    printf("N %zu elapsed-time %.6f sec ", N, elapsed);
    printf("ops-sec %.2f ", (K * N) / elapsed / 1e6);
}

void measure_write_bandwidth(size_t N, size_t K, int *a) {
    volatile int sink = 42;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t t = 0; t < K; t++) {
        for (size_t i = 0; i < N; i++) {
            a[i] = sink;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Write-Bandwidth: ");
    printf("N %zu elapsed-time %.6f sec ", N, elapsed);
    printf("ops-sec %.2f", (K * N) / elapsed / 1e6);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t N = atol(argv[1]);
    size_t K = atol(argv[2]);

    int *a = malloc(N * sizeof(int));
    if (!a) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < N; i++) {
        a[i] = 0;
    }

    for (size_t i = 0; i < N; i++) {
        a[i]++;
    }

    measure_read_bandwidth(N, K, a);

    for (size_t i = 0; i < N; i++) {
        a[i] = 0;
    }

    usleep(100000);

    measure_write_bandwidth(N, K, a);

    printf("\n");
    free(a);
    return 0;
}
