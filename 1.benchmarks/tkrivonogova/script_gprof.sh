#!/bin/bash

REPEATS=100

gcc -pg -o heap ./heap.c

ARRAY_SIZES="10 20 40 60 80 100 200 400 600 800 1000 2000 4000 5000 6000 7000 8000 9000 10000 20000 40000 60000 80000 100000 110000 120000 130000 140000 150000 200000 250000"
files="random_numbers.txt"
for file in $files; do
        echo "Handling file ${file}"
        echo "array_size,time(%),cumulative_time(sec),self_time(sec),calls,self(ms/call),total(ms/call)"
        for size in $ARRAY_SIZES ; do
                taskset -c 3 ./heap "$file" "$size" "$REPEATS"
                gprof ./heap gmon.out > report.txt
                echo "$size,$(awk '{if ($7 == "heap_sort") print $1","$2","$3","$4","$5","$6}' report.txt)"
        done
done
