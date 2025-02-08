#!/bin/bash

if [ $# -lt 3 ]; then
    echo "Usage: $0 <LOG_FILE> <MIN> <MAX>"
    exit 1
fi

LOG_FILE="$1"
MIN_SIZE="$2"      # Minimum size in integers
MAX_SIZE="$3"      # Maximum size in integers
FACTOR=1.1         # Growth factor for sizes
ITERATIONS=20      # Number of times to run each benchmark

echo "Sizes from $MIN_SIZE ints to $MAX_SIZE ints (* $FACTOR each step)."
echo "------------------------------------------------------------"

current_size=$MIN_SIZE
K=1000

while [ "$current_size" -le "$MAX_SIZE" ]; do
    size_in_bytes=$(( current_size * 4 ))
    size_in_kb=$(( size_in_bytes / 1024 ))
    echo "Testing with N = ${current_size} ints (~${size_in_kb} KB), K = ${K} (Total Ops = $(( current_size * K )))"
    
    read_results=()
    write_results=()

    for (( i=1; i<=ITERATIONS; i++ )); do
        echo "Run $i of $ITERATIONS..."
        out=$(./lat "$current_size" "$K")
        sleep 0.1
        echo "$out"
        latency=$(echo "$out" | awk '{print $10}')
        latency_results+=($latency)
    done

    calculate_median() {
        local sorted=($(printf "%s\n" "$@" | sort -n))
        local count=${#sorted[@]}
        if (( count % 2 == 1 )); then
            echo "${sorted[$((count / 2))]}"
        else
            local mid=$((count / 2))
            echo "$(awk "BEGIN {print (${sorted[$mid]} + ${sorted[$((mid - 1))]}) / 2}")"
        fi
    }

    median_latency=$(calculate_median "${latency_results[@]}")
    
    echo "LATENCY: (MEDIAN) ${median_latency}"
    echo "------------------------------------------------------------"

    echo "$current_size $median_latency" >> "$LOG_FILE"

    current_size=$(awk -v cs="$current_size" -v factor="$FACTOR" 'BEGIN {printf "%d", cs*factor}')
done
