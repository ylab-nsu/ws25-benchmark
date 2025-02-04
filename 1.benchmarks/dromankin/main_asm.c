#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

double fmadd(volatile double d, double a, double b, double c) {
    int32_t m = 100000000;
    for (int32_t i = 0; i < m; i++) {
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
    }
    return d;
}

double fmsub(volatile double d, double a, double b, double c) {
    int32_t m = 100000000;
    for (int32_t i = 0; i < m; i++) {
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
        asm volatile("fmsub.d %0, %1, %2, %3"
                     : "=f"(d)
                     : "f"(b), "f"(c), "f"(a));
    }
    return d;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: ./main_asm 1 - fmadd; 2 - fmsub\n");
        exit(1);
    }
    int32_t arg = 0;
    arg = atoi(argv[1]);
    double a = 3.0f;
    double b = 2.0f;
    double c = 4.0f;
    volatile double d = 0.0f;
    switch (arg) {
        case 1:
            d = fmadd(d, a, b, c);
            break;
        case 2:
            d = fmsub(d, a, b, c);
            break;
    }
    return 0;
}
