#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Node {
    long long value;
    struct Node *next;
} Node;

void measure_memory_latency(size_t N, size_t K) {
    Node **nodes = malloc(N * sizeof(Node *));
    if (!nodes) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < N; i++) {
        nodes[i] = malloc(sizeof(Node));
        nodes[i]->value = i;
    }

    srand(time(NULL));
    for (size_t i = 0; i < N; i++) {
        size_t j = rand() % N;
        nodes[i]->next = nodes[j];
    }

    Node *p0 = nodes[0];
    for (size_t i = 0; i < N; i++) {
        volatile int sink = p0->value;
        p0 = p0->next;
    }

    Node *p = nodes[0];
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t t = 0; t < K * N; t++) {
        volatile long long sink = p->value; 
        p = p->next;    
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Pointer-Chasing-Latency: ");
    printf("N %zu ", N);
    printf("Total-Accesses: %zu ", K * N);
    printf("Elapsed-Time: %.6f sec ", elapsed);
    printf("Latency-per-Access: %.2f ns \n", (elapsed * 1e9) / (K * N));

    for (size_t i = 0; i < N; i++) {
        free(nodes[i]);
    }
    free(nodes);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t N = atol(argv[1]);
    size_t K = atol(argv[2]);

    measure_memory_latency(N, K);

    return 0;
}
