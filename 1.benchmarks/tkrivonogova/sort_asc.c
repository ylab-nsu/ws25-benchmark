#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

void heapify(uint32_t arr[], uint32_t n, uint32_t i) {
    uint32_t largest = i;
    uint32_t left = 2 * i + 1;
    uint32_t right = 2 * i + 2;

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

void heap_sort(uint32_t arr[], uint32_t n) {
    for (uint32_t i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (uint32_t i = n - 1; i >= 0; i--) {
        uint32_t temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    FILE* input_file = fopen("random_numbers.txt", "r");
    FILE* output_file = fopen("asc_numbers.txt", "w");
    if (input_file == NULL || output_file == NULL) {
        perror("Open file failed");
        return EXIT_FAILURE;
    }

    uint32_t* numbers = NULL;
    uint32_t count = 0;

    // Выделяем память для массива чисел
    numbers = (uint32_t*)malloc(ARRAY_SIZE * sizeof(uint32_t));
    if (numbers == NULL) {
        perror("Malloc failed");
        return EXIT_FAILURE;
    }

    // Читаем числа из файла
    while (fscanf(input_file, "%" SCNx32, &numbers[count]) == 1) {
        count++;
    }

    // Сортировка чисел по возрастанию (ascending = 1) или убыванию (ascending =
    // 0)
    uint32_t ascending = 1;  // Измените на 0 для сортировки по убыванию
    heap_sort(numbers, count);

    // Запись отсортированных чисел в выходной файл
    for (uint32_t i = 0; i < count; i++) {
        fprintf(output_file, "%u\n", numbers[i]);
    }

    // Освобождение памяти и закрытие файлов
    free(numbers);
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
