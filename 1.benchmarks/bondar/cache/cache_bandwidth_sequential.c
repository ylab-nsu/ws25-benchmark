#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const double BILL = 1e9;
const double MILL = 1e6;
const int SLEEP = 100000;

void measure_read_bandwidth(int num_elements, int num_cycles,
                            const int* data_array) {
    volatile int sink = 0;
    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int cycle_index = 0; cycle_index < num_cycles; cycle_index++) {
        for (int index = 0; index < num_elements; index++) {
            sink = data_array[index];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          ((end_time.tv_nsec - start_time.tv_nsec) / BILL);

    printf("Read-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", num_elements, elapsed_time);
    printf("ops-sec %.2f ", (num_cycles * num_elements) / elapsed_time / MILL);
}

void measure_write_bandwidth(int num_elements, int num_cycles,
                             int* data_array) {
    volatile const int sink = 42;
    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int cycle_index = 0; cycle_index < num_cycles; cycle_index++) {
        for (int index = 0; index < num_elements; index++) {
            data_array[index] = sink;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          ((end_time.tv_nsec - start_time.tv_nsec) / BILL);

    printf("Write-Bandwidth: ");
    printf("N %d elapsed-time %.6f sec ", num_elements, elapsed_time);
    printf("ops-sec %.2f", (num_cycles * num_elements) / elapsed_time / MILL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <K>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_elements = atoi(argv[1]);
    int num_cycles = atoi(argv[2]);

    int* data_array = malloc(num_elements * sizeof(int));
    if (data_array == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }

    for (int index = 0; index < num_elements; index++) {
        data_array[index] = 0;
    }

    for (int index = 0; index < num_elements; index++) {
        data_array[index]++;
    }

    measure_read_bandwidth(num_elements, num_cycles, data_array);

    for (int index = 0; index < num_elements; index++) {
        data_array[index] = 0;
    }

    usleep(SLEEP);

    measure_write_bandwidth(num_elements, num_cycles, data_array);

    printf("\n");
    exit(EXIT_SUCCESS);
}
