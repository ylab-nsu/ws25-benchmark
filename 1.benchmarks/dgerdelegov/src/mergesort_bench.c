#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000

static inline void merge(int array[], int left, int middle, int right);
static inline void mergeSort(int array[], int left, int right);

int main() {
    int *array = malloc(ARRAY_SIZE * sizeof(int));
    if (!array) {
        printf("Ошибка: недостаточно памяти\n");
        return 1;
    }

    // Заполняем массив случайными числами (фиксируем seed для
    // воспроизводимости)
    srand(42);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000000;
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
static inline void merge(int array[], int left, int middle, int right) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    // Временные массивы для левой и правой частей
    int leftArray[leftSize], rightArray[rightSize];

    // Копируем данные в временные массивы
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = array[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightArray[j] = array[middle + 1 + j];
    }

    // Слияние массивов back в основной array[left..right]
    int leftIndex = 0, rightIndex = 0, mergedIndex = left;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[mergedIndex] = leftArray[leftIndex];
            leftIndex++;
        } else {
            array[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }

    // Копируем оставшиеся элементы (если есть)
    while (leftIndex < leftSize) {
        array[mergedIndex++] = leftArray[leftIndex++];
    }
    while (rightIndex < rightSize) {
        array[mergedIndex++] = rightArray[rightIndex++];
    }
}

/*
 Функция сортировки слиянием.
    array - Исходный массив
    left  - Начальный индекс подмассива
    right - Конечный индекс подмассива
 */
static inline void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Рекурсивно сортируем левую и правую половины
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        // Объединяем отсортированные половины
        merge(array, left, middle, right);
    }
}