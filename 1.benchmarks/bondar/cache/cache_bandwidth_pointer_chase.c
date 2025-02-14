#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

const double BILL = 1e9;
const double MILL = 1e6;
const int SLEEP = 100000;

void measure_read_bandwidth(int num_nodes, int num_cycles,
                            node_t** node_array) {
    volatile int sink;
    struct timespec start_time;
    struct timespec end_time;

    node_t* current_node = node_array[0];
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int index = 0; index < num_cycles * num_nodes; index++) {
        sink = current_node->value;
        current_node = current_node->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          ((end_time.tv_nsec - start_time.tv_nsec) / BILL);

    printf("Read-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", num_nodes, elapsed_time);
    printf("ops-sec %f ", (num_cycles * num_nodes) / elapsed_time / MILL);
}

void measure_write_bandwidth(int num_nodes, int num_cycles,
                             node_t** node_array) {
    volatile const int sink = 42;
    struct timespec start_time;
    struct timespec end_time;

    node_t* current_node = node_array[0];
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int index = 0; index < num_cycles * num_nodes; index++) {
        current_node->value = sink;
        current_node = current_node->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          ((end_time.tv_nsec - start_time.tv_nsec) / BILL);

    printf("Write-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", num_nodes, elapsed_time);
    printf("ops-sec %f ", (num_cycles * num_nodes) / elapsed_time / MILL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_nodes = atoi(argv[1]);
    int num_cycles = atoi(argv[2]);

    node_t** node_array = (node_t**)malloc(num_nodes * sizeof(node_t*));
    if (node_array == NULL) {
        perror("failed to allocate memory for node_array");
        exit(EXIT_FAILURE);
    }

    for (int index = 0; index < num_nodes; index++) {
        node_array[index] = malloc(sizeof(node_t));
        if (node_array[index] == NULL) {
            perror("failed to allocate memory for node");
            exit(EXIT_FAILURE);
        }
        node_array[index]->value = index;
    }

    srand(time(NULL));
    for (int index = 0; index < num_nodes; index++) {
        int random_index = rand() % num_nodes;
        node_array[index]->next = node_array[random_index];
    }

    node_t* current_node = node_array[0];
    for (size_t index = 0; index < num_nodes; index++) {
        volatile int warmup_sink = current_node->value;
        current_node = current_node->next;
    }

    measure_read_bandwidth(num_nodes, num_cycles, node_array);

    for (int index = 0; index < num_nodes; index++) {
        node_array[index]->value = index;
    }

    usleep(SLEEP);

    measure_write_bandwidth(num_nodes, num_cycles, node_array);

    printf("\n");

    for (size_t index = 0; index < num_nodes; index++) {
        free(node_array[index]);
    }
    exit(EXIT_SUCCESS);
}
