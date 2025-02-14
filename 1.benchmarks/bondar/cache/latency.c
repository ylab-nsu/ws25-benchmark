#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

const double BILL = 1e9;

void measure_memory_latency(int num_nodes, int num_access_cycles) {
    node_t** node_array = (node_t**)malloc(num_nodes * sizeof(node_t*));
    if (node_array == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }

    for (int index = 0; index < num_nodes; index++) {
        node_array[index] = malloc(sizeof(node_t));
        if (node_array[index] == NULL) {
            perror("Failed malloc");
            exit(EXIT_FAILURE);
        }
        node_array[index]->value = index;
    }

    srand(time(NULL));
    for (int index = 0; index < num_nodes; index++) {
        int random_index = rand() % num_nodes;
        node_array[index]->next = node_array[random_index];
    }

    node_t* warmup_node = node_array[0];
    for (int index = 0; index < num_nodes; index++) {
        volatile int dummy_value = warmup_node->value;
        warmup_node = warmup_node->next;
    }

    node_t* current_node = node_array[0];
    struct timespec start_time;
    struct timespec end_time;
    volatile long long sink;
    int total_accesses = num_access_cycles * num_nodes;

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int index = 0; index < total_accesses; index++) {
        sink = current_node->value;
        current_node = current_node->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          ((end_time.tv_nsec - start_time.tv_nsec) / BILL);

    printf("Pointer-Chasing-Latency: ");
    printf("N %d ", num_nodes);
    printf("Total-Accesses: %d ", total_accesses);
    printf("Elapsed-Time: %.6f sec ", elapsed_time);
    printf("Latency-per-Access: %.2f ns \n",
           (elapsed_time * BILL) / total_accesses);

    for (int index = 0; index < num_nodes; index++) {
        free(node_array[index]);
    }
    free((void*)node_array);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_nodes = atoi(argv[1]);
    int num_access_cycles = atoi(argv[2]);

    measure_memory_latency(num_nodes, num_access_cycles);

    exit(EXIT_SUCCESS);
}
