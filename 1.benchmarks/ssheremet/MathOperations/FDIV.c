
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

double floatDIV(int counter, double main_argument_1, double main_argument_2, double result) {
    double extra_argument_1 = main_argument_1;
    double extra_argument_2 = main_argument_2;

    for (uint32_t i = 0; i < counter; ++i) {
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
        result = main_argument_1 / main_argument_2;
                                     
    }
    return result;
}

int main() {
    volatile int counter = 100000000;
    double main_argument_1, main_argument_2;
    volatile double multi;
    main_argument_1 = 2.5f;
    main_argument_2 = 3.5f;
    result = 1.5f;
    result = floatDIV (counter, main_argument_1, main_argument_2, result);
    return 0;
    
}
