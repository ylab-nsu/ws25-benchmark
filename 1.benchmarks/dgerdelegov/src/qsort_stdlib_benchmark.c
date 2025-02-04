#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

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

    qsort(array, (size_t)ARRAY_SIZE, sizeof(array[0]), compare);

    free(array);
    return 0;
}