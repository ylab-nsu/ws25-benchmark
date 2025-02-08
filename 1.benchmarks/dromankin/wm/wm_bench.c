#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void cnop(int32_t marg) {
    for (int32_t i = 0; i < marg; i++) {
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
        asm volatile("c.nop" : :);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: ./wm_bencn <number of cycles>");
        exit(1);
    }
    volatile int32_t marg = 0;
    marg = atoi(argv[1]);
    cnop(marg);
    return 0;
}
