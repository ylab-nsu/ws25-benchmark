#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "random_data.h"

void quicksort(int array[], int low_index, int high_index) {
    if (low_index >= high_index) {
        return;
    }

    int pivot = array[high_index];
    int partition_index = low_index;

    for (int index = low_index; index < high_index; index++) {
        if (array[index] < pivot) {
            int temporary = array[partition_index];
            array[partition_index] = array[index];
            array[index] = temporary;
            partition_index++;
        }
    }
    int temporary = array[partition_index];
    array[partition_index] = array[high_index];
    array[high_index] = temporary;

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
                "Error: Number of elements to sort (N=%d) exceeds "
                "BASE_ARRAY_SIZE (%d).\n",
                num_elements, BASE_ARRAY_SIZE);
        exit(EXIT_FAILURE);
    }

    int* sort_buffer = (int*)malloc(num_elements * sizeof(int));
    if (sort_buffer == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }

    for (int cycle_index = 0; cycle_index < num_cycles; cycle_index++) {
        memcpy(sort_buffer, base_array, num_elements * sizeof(int));
        quicksort(sort_buffer, 0, num_elements - 1);
    }

    exit(EXIT_SUCCESS);
}
