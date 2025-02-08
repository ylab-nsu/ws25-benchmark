#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define A 4.0F
#define B 1.5F
#define C 2.4F
#define D 8.999F

double fmadd(int32_t marg, volatile double darg, double aarg, double barg,
             double carg) {
    for (int32_t i = 0; i < marg; i++) {
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
    }
    return darg;
}

double fmsub(int32_t marg, volatile double darg, double aarg, double barg,
             double carg) {
    for (int32_t i = 0; i < marg; i++) {
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
        darg = aarg - barg * carg;
    }
    return darg;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: main 1-fmadd; 2 = fmsub\n");
        exit(1);
    }

    int32_t arg = 0;
    arg = atoi(argv[1]);
    volatile int32_t marg = 0;
    marg = atoi(argv[2]);
    volatile double aarg;
    volatile double barg;
    volatile double darg;
    volatile double carg;
    aarg = A;
    barg = B;
    carg = C;
    darg = D;

    switch (arg) {
        case 1:
            aarg = fmadd(marg, darg, aarg, barg, carg);
            break;
        case 2:
            aarg = fmsub(marg, darg, aarg, barg, carg);
            break;
        default:
            break;
    }

    return 0;
}
