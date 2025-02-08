#!/bin/bash
gcc  -fno-verbose-asm -march=rv64idc wm_bench.c -o wm_bench -O0 -pg
rep=20
iter=10000
n=10000000

for ((i = 1; i < $n + 1; i+=$iter))
do
perf stat -o out.txt -r $rep --table ./wm_bench $i
grep ") #" out.txt > out2.txt
cat out2.txt | cut -d"(" -f1 >> out3.txt
done
