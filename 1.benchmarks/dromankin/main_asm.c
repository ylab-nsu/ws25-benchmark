#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define A 3.0F
#define B 2.0F
#define C 4.0F
#define D 0.0F

double fmadd(int marg, volatile double darg, double aarg, double barg,
             double carg) {
  for (int32_t i = 0; i < marg; i++) {
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmadd.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
  }
  return darg;
}

double fmsub(int marg, volatile double darg, double aarg, double barg,
             double carg) {
  for (int32_t i = 0; i < marg; i++) {
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
    asm volatile("fmsub.d %0, %1, %2, %3"
                 : "=f"(darg)
                 : "f"(barg), "f"(carg), "f"(aarg));
  }
  return darg;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("usage: ./main_asm 1 - fmadd; 2 - fmsub\n");
    exit(1);
  }
  int32_t arg = 0;
  arg = atoi(argv[1]);
  volatile int marg = 0;
  marg = atoi(argv[2]);
  double aarg = A;
  double barg = B;
  double carg = C;
  volatile double darg = D;
  switch (arg) {
    case 1:
      darg = fmadd(marg, darg, aarg, barg, carg);
      break;
    case 2:
      darg = fmsub(marg, darg, aarg, barg, carg);
      break;
    default:
      break;
  }
  return 0;
}
