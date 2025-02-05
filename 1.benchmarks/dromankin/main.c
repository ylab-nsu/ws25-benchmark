#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

double fmadd(int m, volatile double d, double a, double b, double c) {
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

double fmsub(int m, volatile double d, double a, double b, double c) {
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
    if (argc != 3) {
        printf("usage: main 1-fmadd; 2 = fmsub\n");
        exit(1);
    }

    int32_t arg = 0;
    arg = atoi(argv[1]);
    volatile int m = 0;
    m = atoi(argv[2]);
    volatile double a, b, c, d;
    a = 4.0f;
    b = 1.5f;
    c = 2.4f;
    d = 8.999f;

    switch (arg) {
        case 1:
            a = fmadd(m, d, a, b, c);
            break;
        case 2:
            a = fmsub(m, d, a, b, c);
            break;
    }

    return 0;
}
