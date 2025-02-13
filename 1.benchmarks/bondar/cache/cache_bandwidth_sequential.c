#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void measure_read_bandwidth(int n, int k, const int* a) {
    volatile int sink = 0;
    struct timespec start;
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int t = 0; t < k; t++) {
        for (int i = 0; i < n; i++) {
            sink = a[i];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);

    printf("Read-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", n, elapsed);
    printf("ops-sec %.2f ", (k * n) / elapsed / 1e6);
}

void measure_write_bandwidth(int n, int k, int* a) {
    volatile int sink = 42;
    struct timespec start;
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int t = 0; t < k; t++) {
        for (int i = 0; i < n; i++) {
            a[i] = sink;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);

    printf("Write-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", n, elapsed);
    printf("ops-sec %.2f", (k * n) / elapsed / 1e6);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    int* a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        a[i]++;
    }

    measure_read_bandwidth(n, k, a);

    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }

    usleep(100000);

    measure_write_bandwidth(n, k, a);

    printf("\n");
    exit(EXIT_SUCCESS);
}
