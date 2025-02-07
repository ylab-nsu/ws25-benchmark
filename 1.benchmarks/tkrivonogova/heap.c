#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(uint32_t arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        uint32_t temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heap_sort(uint32_t arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        uint32_t temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void read_numbers_from_file(const char* filename, uint32_t arr[],
                            int array_size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array_size; i++) {
        fscanf(file, "%" SCNx32, &arr[i]);
    }

    fclose(file);
}

void shuffle_array(uint32_t arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Обмен arr[i] и arr[j]
        uint32_t temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main(int argc, char* argv[]) {
    srand(42);
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file> <size> <repeats>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    int array_size = atoi(argv[2]);
    int repeats_number = atoi(argv[3]);

    uint32_t* arr = malloc(array_size * sizeof(uint32_t));
    if (arr == NULL) {
        perror("Malloc failed");
        return EXIT_FAILURE;
    }

    read_numbers_from_file(filename, arr, array_size);

    for (int i = 0; i < repeats_number; ++i) {
        // Переупорядочивание массива
        shuffle_array(arr, array_size);
        heap_sort(arr, array_size);
    }

    free(arr);

    return EXIT_SUCCESS;
}
