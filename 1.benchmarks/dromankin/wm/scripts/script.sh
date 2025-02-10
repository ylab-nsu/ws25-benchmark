#!/bin/bash
cd ../
gcc  -fno-verbose-asm -march=rv64idc wm_bench.c -o wm_bench -O0 -pg
perf record -e cpu-clock ./wm_bench $1 $2
perf report
