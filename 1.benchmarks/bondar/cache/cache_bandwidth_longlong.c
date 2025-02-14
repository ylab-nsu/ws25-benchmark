
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct node {
    long long value;
    struct node* next;
} node_t;

const double BILL = 1e9;
const double MILL = 1e6;
const int SLEEP = 100000;

void measure_read_bandwidth(int num_nodes, int num_cycles,
                            node_t** node_array) {
    volatile long long sink;
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
    volatile const long long sink = 42LL;
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
    printf("ops-sec %f", (num_cycles * num_nodes) / elapsed_time / MILL);
}

int main(int arg_count, char* arg_vector[]) {
    if (arg_count != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", arg_vector[0]);
        exit(EXIT_FAILURE);
    }

    int num_nodes = atoi(arg_vector[1]);
    int num_cycles = atoi(arg_vector[2]);

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
        node_array[index]->value = (long long)index;
    }

    srand(time(NULL));
    for (int index = 0; index < num_nodes; index++) {
        size_t random_index = rand() % num_nodes;
        node_array[index]->next = node_array[random_index];
    }

    node_t* current_node = node_array[0];
    for (int index = 0; index < num_nodes; index++) {
        volatile long long sink = current_node->value;
        current_node = current_node->next;
    }

    measure_read_bandwidth(num_nodes, num_cycles, node_array);

    for (int index = 0; index < num_nodes; index++) {
        node_array[index]->value = 0LL;
    }

    usleep(SLEEP);

    measure_write_bandwidth(num_nodes, num_cycles, node_array);

    printf("\n");
    for (int index = 0; index < num_nodes; index++) {
        free(node_array[index]);
    }
    exit(EXIT_SUCCESS);
}
