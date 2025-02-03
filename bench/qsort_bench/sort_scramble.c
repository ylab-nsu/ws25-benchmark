#include <stdio.h>
#include <stdlib.h>
#include "random_data.h"  // Include the header with pre-generated data

void scramble(int *arr, int n, int cycle) {
    for (int i = 0; i < n; i++) {
        uint32_t seed = (cycle * 0x5bd1e995) + (i * 0xdeadbeef);
        seed ^= (seed >> 16);

        arr[i] ^= seed; 
        arr[i] = (arr[i] << 3) | (arr[i] >> (32 - 3)); 
        arr[i] += (seed ^ 0x9e3779b9);
    }
}

void quicksort(int arr[], int low, int high) {
    if (low >= high)
        return;
    
    int pivot = arr[high];
    int i = low;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;
    
    quicksort(arr, low, i - 1);
    quicksort(arr, i + 1, high);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <M (number of cycles)> <N (number of elements to sort)>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    
    if (N > BASE_ARRAY_SIZE) {
        fprintf(stderr, "Error: Number of elements to sort (N=%d) exceeds BASE_ARRAY_SIZE (%d).\n", N, BASE_ARRAY_SIZE);
        return EXIT_FAILURE;
    }
    
    int *buffer = malloc(N * sizeof(int));
    if (!buffer) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    
    for (int cycle = 0; cycle < M; cycle++) {
        scramble(buffer, N, cycle);
        quicksort(buffer, 0, N - 1);
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}
