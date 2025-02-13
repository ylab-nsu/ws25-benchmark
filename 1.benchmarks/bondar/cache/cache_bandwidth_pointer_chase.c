#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

void measure_read_bandwidth(int n, int k, node_t** nodes) {
    volatile int sink = 0;
    struct timespec start;
    struct timespec end;

    node_t* p = nodes[0];
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int t = 0; t < k * n; t++) {
        sink = p->value;
        p = p->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);

    printf("Read-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", n, elapsed);
    printf("ops-sec %f ", k * n / elapsed / 1e6);
}

void measure_write_bandwidth(int n, int k, node_t** nodes) {
    volatile int sink = 42;
    struct timespec start;
    struct timespec end;

    node_t* p = nodes[0];
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int t = 0; t < k * n; t++) {
        p->value = sink;
        p = p->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);

    printf("Write-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", n, elapsed);
    printf("ops-sec %f ", k * n / elapsed / 1e6);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    node_t** nodes = (node_t**)malloc(n * sizeof(node_t*));
    if (nodes == NULL) {
        perror("Failed to allocate memory for nodes array");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        nodes[i] = malloc(sizeof(node_t));
        if (nodes[i] == NULL) {
            perror("Failed to allocate memory for nodes array");
            exit(EXIT_FAILURE);
        }
        nodes[i]->value = i;
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        nodes[i]->next = nodes[j];
    }

    node_t* p = nodes[0];
    for (size_t i = 0; i < n; i++) {
        volatile int sink = p->value;
        p = p->next;
    }

    measure_read_bandwidth(n, k, nodes);

    for (int i = 0; i < n; i++) {
        nodes[i]->value = i;
    }

    usleep(100000);

    measure_write_bandwidth(n, k, nodes);

    printf("\n");

    for (size_t i = 0; i < n; i++) {
        free(nodes[i]);
    }

    exit(EXIT_SUCCESS);
}
