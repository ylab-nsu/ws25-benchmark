#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "random_data.h"

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
        memcpy(buffer, base_array, N * sizeof(int));
        
        for (int i = 0; i < N; i++) {
            buffer[i] ^= (cycle * 0x5bd1e995);
        }
        
        quicksort(buffer, 0, N - 1);
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}
