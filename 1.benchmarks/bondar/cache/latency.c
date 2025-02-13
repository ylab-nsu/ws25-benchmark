#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

void measure_memory_latency(int n, int k) {
    node_t** nodes = (node_t**)malloc(n * sizeof(node_t*));
    if (nodes == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        nodes[i] = malloc(sizeof(node_t));
        if (nodes[i] == NULL) {
            perror("Failed malloc");
            exit(EXIT_FAILURE);
        }
        nodes[i]->value = i;
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int j = rand() % N;
        nodes[i]->next = nodes[j];
    }

    node_t* p0 = nodes[0];
    for (int i = 0; i < n; i++) {
        volatile int sink = p0->value;
        p0 = p0->next;
    }

    node_t* p = nodes[0];
    struct timespec start;
    struct timespec end;
    volatile long long sink;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int t = 0; t < k * n; t++) {
        sink = p->value;
        p = p->next;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);

    printf("Pointer-Chasing-Latency: ");
    printf("N %d ", n);
    printf("Total-Accesses: %d ", k * n);
    printf("Elapsed-Time: %.6f sec ", elapsed);
    printf("Latency-per-Access: %.2f ns \n", (elapsed * 1e9) / (k * n));

    for (int i = 0; i < n; i++) {
        free(nodes[i]);
    }
    free((void*)nodes);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    measure_memory_latency(n, k);

    exit(EXIT_SUCCESS);
}
