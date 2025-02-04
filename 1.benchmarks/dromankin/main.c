
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

double fmadd(volatile double d, double a, double b, double c) {
    int32_t m = 100000000;
    for (int32_t i = 0; i < m; i++) {
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
        d = a + b * c;
    }
    return d;
}

double fmsub(volatile double d, double a, double b, double c) {
    int32_t m = 1000000000;
    for (int32_t i = 0; i < m; i++) {
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
        d = a - b * c;
    }
    return d;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: main 1-fmadd; 2 = fmsub\n");
        exit(1);
    }

    int32_t arg = 0;
    arg = atoi(argv[1]);
    volatile double a, b, c, d;
    a = 4.0f;
    b = 1.5f;
    c = 2.4f;
    d = 8.999f;

    switch (arg) {
        case 1:
            a = fmadd(d, a, b, c);
            break;
        case 2:
            a = fmsub(d, a, b, c);
            break;
    }

    return 0;
}
