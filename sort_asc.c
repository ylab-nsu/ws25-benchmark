#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

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

int main() {
    FILE *input_file = fopen("random_numbers.txt", "r");
    FILE *output_file = fopen("asc_numbers.txt", "w");
    if (input_file == NULL || output_file == NULL) {
        perror("Open file failed");
        return EXIT_FAILURE;
    }

    int *numbers = NULL;
    int count = 0;

    // Выделяем память для массива чисел
    numbers = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (numbers == NULL) {
        perror("Malloc failed");
        return EXIT_FAILURE;
    }

    // Читаем числа из файла
    while (fscanf(input_file, "%d", &numbers[count]) == 1) {
        count++;
    }

    // Сортировка чисел по возрастанию (ascending = 1) или убыванию (ascending = 0)
    int ascending = 1; // Измените на 0 для сортировки по убыванию
    heap_sort(numbers, count);

    // Запись отсортированных чисел в выходной файл
    for (int i = 0; i < count; i++) {
        fprintf(output_file, "%d\n", numbers[i]);
    }

    // Освобождение памяти и закрытие файлов
    free(numbers);
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}

