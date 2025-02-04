#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000
#define SEED 50

// Функция сравнения для qsort()
int compare(const void *a, const void *b) {
    int32_t x = *(const int32_t *)a, y = *(const int32_t *)b;
    return (x > y) - (x < y);
}

int main() {
    int32_t *array = malloc(ARRAY_SIZE * sizeof(int32_t));
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

    qsort(array, (size_t)ARRAY_SIZE, sizeof(array[0]), compare);

    free(array);
    return 0;
}
