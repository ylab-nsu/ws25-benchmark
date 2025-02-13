#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void measure_read_bandwidth(size_t N, size_t K, Node** nodes) {
    volatile int sink = 0;
    struct timespec start, end;

    Node* p = nodes[0];
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t t = 0; t < K * N; t++) {
        sink = p->value;
        p = p->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Read-Bandwidth: ");
    printf("N %zu elapsed-time %.6f sec ", N, elapsed);
    printf("ops-sec %f ", K * N / elapsed / 1e6);
}

void measure_write_bandwidth(size_t N, size_t K, Node** nodes) {
    volatile int sink = 42;
    struct timespec start, end;

    Node* p = nodes[0];
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t t = 0; t < K * N; t++) {
        p->value = sink;
        p = p->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Write-Bandwidth: ");
    printf("N %zu elapsed-time %.6f sec ", N, elapsed);
    printf("ops-sec %f ", K * N / elapsed / 1e6);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t N = atol(argv[1]);
    size_t K = atol(argv[2]);

    Node** nodes = malloc(N * sizeof(Node*));
    for (size_t i = 0; i < N; i++) {
        nodes[i] = malloc(sizeof(Node));
        nodes[i]->value = i;
    }

    srand(time(NULL));
    for (size_t i = 0; i < N; i++) {
        size_t j = rand() % N;
        nodes[i]->next = nodes[j];
    }

    Node* p = nodes[0];
    for (size_t i = 0; i < N; i++) {
        volatile int sink = p->value;
        p = p->next;
    }

    measure_read_bandwidth(N, K, nodes);

    for (size_t i = 0; i < N; i++) {
        nodes[i]->value = i;
    }

    usleep(100000);

    measure_write_bandwidth(N, K, nodes);

    printf("\n");

    for (size_t i = 0; i < N; i++) {
        free(nodes[i]);
    }
    free(nodes);

    return 0;
}
