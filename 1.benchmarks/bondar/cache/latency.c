#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

const double BILL = 1e9;

void measure_memory_latency(int num_nodes, int num_cycles, node_t* head) {
    node_t* current_node = head;
    struct timespec start_time;
    struct timespec end_time;
    volatile long long sink;

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int index = 0; index < num_cycles; index++) {
        while (current_node != NULL) {
            sink = current_node->value;
            current_node = current_node->next;
        }
        current_node = head;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time =
        ((double)(end_time.tv_sec - start_time.tv_sec)) +
        (((double)(end_time.tv_nsec - start_time.tv_nsec)) / BILL);

    printf("Pointer-Chasing-Latency: ");
    printf("N %d ", num_nodes);
    printf("Total-Accesses: %d ", num_cycles * num_nodes);
    printf("Elapsed-Time: %.6f sec ", elapsed_time);
    printf("Latency-per-Access: %.2f ns \n",
           (elapsed_time * BILL) / (num_cycles * num_nodes));
}

node_t* create_list(int num_nodes) {
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
        node_array[index]->next = NULL;
    }

    int link_indices[num_nodes];
    for (int i = 0; i < num_nodes; i++) {
        link_indices[i] = i;
    }

    // Fisher-Yates shuffle
    for (int index = num_nodes - 1; index > 0; index--) {
        int random_index = (int)arc4random_uniform(index + 1);
        int temp = link_indices[index];
        link_indices[index] = link_indices[random_index];
        link_indices[random_index] = temp;
    }

    for (int i = 0; i < num_nodes - 1; i++) {
        node_array[link_indices[i]]->next = node_array[link_indices[i + 1]];
    }
    node_array[link_indices[num_nodes - 1]]->next = NULL;

    node_t* head = node_array[link_indices[0]];
    free((void*)node_array);
    return head;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_nodes = atoi(argv[1]);
    int num_access_cycles = atoi(argv[2]);

    node_t* head = create_list(num_nodes);

    node_t* current_node = head;
    volatile int warmup_sink;
    while (current_node->next != NULL) {
        warmup_sink = current_node->value;
        current_node = current_node->next;
    }

    measure_memory_latency(num_nodes, num_access_cycles, head);

    while (head != NULL) {
        node_t* temp = head;
        head = head->next;
        free(temp);
    }

    exit(EXIT_SUCCESS);
}
