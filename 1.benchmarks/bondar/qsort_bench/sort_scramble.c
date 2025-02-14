
#include <stdio.h>
#include <stdlib.h>
#include "random_data.h"

void scramble(int* array, int size, int cycle_index) {
    for (int index = 0; index < size; index++) {
        unsigned int seed = (cycle_index * 0x5bd1e995) + (index * 0xdeadbeef);
        seed ^= (seed >> 16);

        array[index] ^= seed;
        array[index] = (array[index] << 3) | (array[index] >> (32 - 3));
        array[index] += (seed ^ 0x9e3779b9);
    }
}

void quicksort(int array[], int low_index, int high_index) {
    if (low_index >= high_index)
        return;

    int pivot_value = array[high_index];
    int partition_index = low_index;

    for (int index = low_index; index < high_index; index++) {
        if (array[index] < pivot_value) {
            int temp_value = array[partition_index];
            array[partition_index] = array[index];
            array[index] = temp_value;
            partition_index++;
        }
    }
    int temp_value = array[partition_index];
    array[partition_index] = array[high_index];
    array[high_index] = temp_value;

    quicksort(array, low_index, partition_index - 1);
    quicksort(array, partition_index + 1, high_index);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <num_cycles (number of cycles)> <num_elements "
                "(number of elements to sort)>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_cycles = atoi(argv[1]);
    int num_elements = atoi(argv[2]);

    if (num_elements > BASE_ARRAY_SIZE) {
        fprintf(stderr,
                "Error: Number of elements to sort (num_elements=%d) exceeds "
                "BASE_ARRAY_SIZE (%d).\n",
                num_elements, BASE_ARRAY_SIZE);
        exit(EXIT_FAILURE);
    }

    int* buffer = (int*)malloc(num_elements * sizeof(int));
    if (buffer == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }

    for (int cycle_index = 0; cycle_index < num_cycles; cycle_index++) {
        scramble(buffer, num_elements, cycle_index);
        quicksort(buffer, 0, num_elements - 1);
    }

    exit(EXIT_SUCCESS);
}
