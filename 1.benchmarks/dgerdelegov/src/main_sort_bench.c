#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static inline void merge(int32_t array[], size_t left, size_t middle,
                         size_t right);
static inline void mergeSort(int32_t array[], size_t left, size_t right);
int compare(const void *a, const void *b);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf(
            "Использование: %s <размер массива> <сортировка>"
            " (m - mergesort; q - qsort), <seed> (-1 - случайный)\n",
            argv[0]);
        return 1;
    }

    uint32_t size = (uint32_t)atoi(argv[1]);
    if (size == 0) {
        printf("Ошибка: размер массива должен быть больше 0\n");
        return 1;
    }

    int32_t *array = malloc(size * sizeof(int32_t));
    if (!array) {
        printf("Ошибка: недостаточно памяти\n");
        return 1;
    }

    int seed = atoi(argv[3]);
    srand(seed == -1 ? (unsigned int)time(NULL) : (unsigned int)seed);

    for (size_t i = 0; i < size; i++) {
        array[i] = (int32_t)(rand() % 1000000);
    }

    if (strcmp(argv[2], "m") == 0) {
        mergeSort(array, 0, size - 1);
    } else if (strcmp(argv[2], "q") == 0) {
        qsort(array, (size_t)size, sizeof(array[0]), compare);
    } else {
        printf("Ошибка: укажите 'm' для mergesort или 'q' для qsort\n");
        free(array);
        return 1;
    }

    free(array);
    return 0;
}

/*
 Функция объединяет два подмассива в один отсортированный.
    array  - Исходный массив
    left   - Начальный индекс левого подмассива
    middle - Индекс, который разделяет массив на две части
    right  - Конечный индекс правого подмассива
*/
static inline void merge(int32_t array[], size_t left, size_t middle,
                         size_t right) {
    size_t leftSize = middle - left + 1;
    size_t rightSize = right - middle;

    int32_t *leftArray = malloc(leftSize * sizeof(int32_t));
    int32_t *rightArray = malloc(rightSize * sizeof(int32_t));

    if (!leftArray || !rightArray) {
        printf("Ошибка: недостаточно памяти при слиянии\n");
        free(leftArray);
        free(rightArray);
        return;
    }

    memcpy(leftArray, &array[left], leftSize * sizeof(int32_t));
    memcpy(rightArray, &array[middle + 1], rightSize * sizeof(int32_t));

    size_t leftIndex = 0, rightIndex = 0, mergedIndex = left;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[mergedIndex++] = leftArray[leftIndex++];
        } else {
            array[mergedIndex++] = rightArray[rightIndex++];
        }
    }

    while (leftIndex < leftSize) {
        array[mergedIndex++] = leftArray[leftIndex++];
    }
    while (rightIndex < rightSize) {
        array[mergedIndex++] = rightArray[rightIndex++];
    }

    free(leftArray);
    free(rightArray);
}

/*
 Функция сортировки слиянием.
    array - Исходный массив
    left  - Начальный индекс подмассива
    right - Конечный индекс подмассива
*/
static inline void mergeSort(int32_t array[], size_t left, size_t right) {
    if (left < right) {
        size_t middle = left + (right - left) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

// Функция сравнения для qsort()
int compare(const void *a, const void *b) {
    int32_t x = *(const int32_t *)a, y = *(const int32_t *)b;
    return (x > y) - (x < y);
}
