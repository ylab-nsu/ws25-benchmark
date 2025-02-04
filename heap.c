#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void read_numbers_from_file(const char *filename, int arr[], int array_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array_size; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
}

void shuffle_array(int arr[], int n) {
    //srand(42); // Инициализация генератора случайных чисел
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Обмен arr[i] и arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main(int argc, char *argv[]) {
    srand(42);
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file> <size> <repeats>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int array_size = atoi(argv[2]);
    int repeats_number = atoi(argv[3]);
    
    int *arr = malloc(array_size * sizeof(int));
    if (arr == NULL) {
        perror("Malloc failed");
        return EXIT_FAILURE;
    }

    read_numbers_from_file(filename, arr, array_size);

    for (int i = 0; i < repeats_number; ++i) {
    	// Переупорядочивание массива
    	shuffle_array(arr, array_size);
	/*for (int i = 0; i < 5; ++i) {
            printf("%d ", arr[i]);
        }
	printf("\t");*/

    	heap_sort(arr, array_size);

    	/*for (int i = 0; i < 5; ++i) {
	    printf("%d ", arr[i]);
    	}
    	printf("\n");*/
    }
    
    free(arr);
    
    return EXIT_SUCCESS;
}

