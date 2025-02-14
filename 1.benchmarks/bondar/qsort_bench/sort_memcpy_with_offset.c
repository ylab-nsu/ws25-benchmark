#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "random_data.h"

void quicksort(short array[], int low_index, int high_index) {
    if (low_index >= high_index)
        return;

    short pivot_value = array[high_index];
    int partition_index = low_index;

    for (int index = low_index; index < high_index; index++) {
        if (array[index] < pivot_value) {
            short temp_value = array[partition_index];
            array[partition_index] = array[index];
            array[index] = temp_value;
            partition_index++;
        }
    }

    short temp_value = array[partition_index];
    array[partition_index] = array[high_index];
    array[high_index] = temp_value;

    quicksort(array, low_index, partition_index - 1);
    quicksort(array, partition_index + 1, high_index);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <M (number of cycles)> <N (number of elements to "
                "sort)>\n",
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

    short* buffer = (short*)malloc(num_elements * sizeof(int));
    if (buffer == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }

    size_t max_offset = BASE_ARRAY_SIZE - num_elements;
    const unsigned prime = 0x5bd1e995;

    for (int cycle_index = 0; cycle_index < num_cycles; cycle_index++) {
        size_t offset = ((1ULL * cycle_index * prime) % (max_offset + 1));
        memcpy(buffer, base_array + offset, num_elements * sizeof(short));

        quicksort(buffer, 0, num_elements - 1);
    }

    exit(EXIT_SUCCESS);
}
