#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void cnop(int m) {
    for (int32_t i = 0; i < m; i++) {
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
        asm volatile("c.nop"
                     :
                     :
        );
    }
}

int cor(int m, int a) {
	asm volatile("c.or x0, x0"
                     :
                     :
        );
	return a;
}
/*
int candi (int m, int a) {
	asm volatile("c.andi %0, 0b011111"
                     :"=&r"(a)
                     :"r"(a)
        );
	return a;
}

int csub (int m, int a) {
	asm volatile("c.sub %0, %1"
                     :"=&r"(a)
                     :"r"(a)
        );
	return a;
}
*/

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: ./main_asm 1 - cnop; 2 - c.or\n");
        exit(1);
    }

    int32_t arg = 0;
    arg = atoi(argv[1]);
    volatile int m = 0;
    m = atoi(argv[2]);
    int a = 0xab;
    int b = 0xcd;
    printf("%d\n", a);
    a = cor(m, a);
    printf("%d\n", a);
/*
    switch (arg) {
        case 1:
            cnop(m);
            break;
        default:
            break;
    }
*/
    return 0;
}


