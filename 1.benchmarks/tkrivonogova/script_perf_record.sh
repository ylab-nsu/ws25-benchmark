#!/bin/bash

REPEATS=100

gcc -pg -O0 -o heap ./heap.c
event="task-clock"

ARRAY_SIZES="10 20 40 60 80 100 200 400 600 800 1000 2000 4000 5000 6000 7000 8000 9000 10000 15000 20000 25000 30000 35000 40000 45000 50000 55000 60000 65000 70000 75000 80000 85000 90000 95000 100000 110000 120000 130000 140000 150000 160000 180000 200000 250000 300000 350000"
files="random_numbers.txt"
for file in $files; do
        echo "Handling file ${file}"
        echo "array_size,events_count"
        for size in $ARRAY_SIZES ; do
                perf record -e "$event" taskset -c 1 ./heap random_numbers.txt "$size" "$REPEATS" &> /dev/null
                perf report > report.txt
                events_total=$(grep -m1 'Event count (approx.): ' report.txt | awk -F: '{print $2}' | tr -d ',')
                events_heapify_percent=$(grep -m1 'heapify' report.txt | awk '{print $1}' | tr -d ',' | tr -d '%')
                events_heap_sort_percent=$(grep -m1 'heap_sort' report.txt | awk '{print $1}' | tr -d ',' | tr -d '%')
                events_count=$(echo "$events_total,$events_heapify_percent,$events_heap_sort_percent" | awk -F, '{result=$1*($2 + $3) / 100; printf "%.10f\n", result}' 2>/dev/null)
                echo "$size,$events_count"
        done
done
