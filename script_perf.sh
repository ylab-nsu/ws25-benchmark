#!/bin/bash

REPEATS=1000

gcc -pg -o heap ./heap.c

ARRAY_SIZES="10 20 40 60 80 100 200 400 600 800 1000 2000 4000 5000 6000 7000 8000 9000 10000 20000 40000 60000 80000 100000 110000 120000 130000 140000 150000"
files="random_numbers.txt"
for file in $files; do
        echo "Handling file ${file}"
        echo "array_size,task-clock,context-switches,CPU-migrations,page-faults,cycles,instructions,branches,branch-misses"
        for size in $ARRAY_SIZES ; do
                perf stat -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses taskset -c 1 ./heap random_numbers.txt "$size" "$REPEATS" &> perf.log
                task_clock=$(grep -m1 'task-clock' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                context_switches=$(grep -m1 'context-switches' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                cpu_migrations=$(grep -m1 'cpu-migrations' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                page_faults=$(grep -m1 'page-faults' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                cycles=$(grep -m1 'cycles' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                instructions=$(grep -m1 'instructions' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                branches=$(grep -m1 'branches' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                branch_misses=$(grep -m1 'branch-misses' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                echo "$size,$task_clock,$context_switches,$cpu_migrations,$page_faults,$cycles,$instructions,$branches,$branch_misses"
        done
done
