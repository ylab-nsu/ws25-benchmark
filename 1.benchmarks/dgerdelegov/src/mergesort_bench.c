#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 1000
#define SEED 50

static inline void merge(int32_t array[], size_t left, size_t middle,
                         size_t right);
static inline void mergeSort(int32_t array[], size_t left, size_t right);

int main() {
    int32_t* array = malloc(ARRAY_SIZE * sizeof(int32_t));
    if (!array) {
        printf("Ошибка: недостаточно памяти\n");
        return 1;
    }

    // Заполняем массив случайными числами (фиксируем seed для
    // воспроизводимости)
    srand(SEED);
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = (int32_t)(rand() % 1000000);
    }

    mergeSort(array, 0, ARRAY_SIZE - 1);

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

    int32_t* leftArray = malloc(leftSize * sizeof(int32_t));
    int32_t* rightArray = malloc(rightSize * sizeof(int32_t));

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
