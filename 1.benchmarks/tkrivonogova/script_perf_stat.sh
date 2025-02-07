#!/bin/bash

REPEATS=100

gcc -pg -o heap ./heap.c

ARRAY_SIZES="10 20 40 60 80 100 200 400 600 800 1000 2000 4000 5000 6000 7000 8000 9000 10000 20000 40000 60000 80000 100000 110000 120000 130000 140000 150000 160000 180000 200000 250000 300000 350000"
files="random_numbers.txt asc_numbers.txt desc_numbers.txt"
for file in $files; do
        echo "Handling file ${file}"
        echo "array_size,task-clock,context-switches,CPU-migrations,page-faults,cycles,instructions,branches,branch-misses,l1d_access,l1d_miss,l1d_store_access,l2_load_access,l2_miss,l2_store_access"
        for size in $ARRAY_SIZES ; do
                perf stat -r 10 -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,l1d_access,l1d_miss,l1d_store_access,l2_load_access,l2_miss,l2_store_access taskset -c 1 ./heap random_numbers.txt "$size" "$REPEATS" &> perf.log
                task_clock=$(grep -m1 'task-clock' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                context_switches=$(grep -m1 'context-switches' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                cpu_migrations=$(grep -m1 'cpu-migrations' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                page_faults=$(grep -m1 'page-faults' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                cycles=$(grep -m1 'cycles' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                instructions=$(grep -m1 'instructions' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                branches=$(grep -m1 'branches' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                branch_misses=$(grep -m1 'branch-misses' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                l1d_access=$(grep -m1 'l1d_access' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                l1d_miss=$(grep -m1 'l1d_miss' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                l1d_store_access=$(grep -m1 'l1d_store_access' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                l2_load_access=$(grep -m1 'l2_load_access' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                l2_miss=$(grep -m1 'l2_miss' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                l2_store_access=$(grep -m1 'l2_store_access' perf.log | grep -v "<not counted>" | awk '{print $1}' | tr -d ',')
                echo "$size,$task_clock,$context_switches,$cpu_migrations,$page_faults,$cycles,$instructions,$branches,$branch_misses,$l1d_access,$l1d_miss,$l1d_store_access,$l2_load_access,$l2_miss,$l2_store_access"
        done
done
