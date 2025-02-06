#!/bin/bash

sizes=(10 20 40 60 80 100 200 400 600 800 1000 2000 4000 5000 6000 7000 8000 9000 10000 20000 40000 60000 80000 100000 110000 120000 130000 140000 150000 200000 400000 500000 600000 750000 1000000)
num_runs=15 # Количество измерений

# Выходные файлы
output_mergesort="result/results_mergesort.txt"
output_qsort="result/results_qsort.txt"

# Очистка предыдущих результатов
> "$output_mergesort"
> "$output_qsort"

# Начальный сид
seed=42  

for size in "${sizes[@]}"; do
    echo "Тестирование размера: $size, сид: $seed"

    # Измерение времени работы mergesort
    ms_time=$(taskset -c 3 perf stat -r $num_runs ./bin/main_sort_bench "$size" m "$seed" 2>&1 | \
              awk '/msec task-clock/ {print $1}')  

    if [[ -n "$ms_time" ]]; then
        echo "$size, $ms_time" >> "$output_mergesort"
    else
        echo "$size, ERROR" >> "$output_mergesort"
    fi

    # Измерение времени работы qsort
    qs_time=$(taskset -c 3 perf stat -r $num_runs ./bin/main_sort_bench "$size" q "$seed" 2>&1 | \
              awk '/msec task-clock/ {print $1}')

    if [[ -n "$qs_time" ]]; then
        echo "$size, $qs_time" >> "$output_qsort"
    else
        echo "$size, ERROR" >> "$output_qsort"
    fi

    seed=$((seed + 1))
done

echo "Тестирование завершено. Результаты сохранены в $output_mergesort и $output_qsort"
