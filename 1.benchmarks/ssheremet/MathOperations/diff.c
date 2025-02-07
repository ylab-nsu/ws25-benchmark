#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

double floatDIFF(int m, double y, double l, double multi) {
    double e = y;
    double d = l;
    for (uint32_t i = 0; i < m; ++i) {
        multi = e - d;
        multi = e - d;
        multi = e - d;
        multi = e - d;
        multi = e - d;
        multi = e - d;  
        multi = e - d;
        multi = e - d;
        multi = e - d;
        multi = e - d;
        multi = e - d;
        multi = e - d;
        multi = e - d;  
        multi = e - d;                                             
    }
    return multi;
}

int main() {
    volatile int m = 100000000;
    double e,d;
    volatile double multi;
    e = 2.5f;
    d = 3.5f;
    multi = 1.5f;
    multi = floatDIFF (m, e, d, multi);
    return 0;
    
}
