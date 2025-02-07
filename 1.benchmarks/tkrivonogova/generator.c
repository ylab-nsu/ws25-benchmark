#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000000

void generate_random_numbers(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    srand(42);  // Фиксированный сид для генерации случайных чисел

    for (int i = 0; i < ARRAY_SIZE; i++) {
        int random_number = rand() % 100000;  // Генерация числа от 0 до 99999
        fprintf(file, "%d\n", random_number);
    }

    fclose(file);
}

int main() {
    generate_random_numbers("random_numbers.txt");
    return 0;
}
