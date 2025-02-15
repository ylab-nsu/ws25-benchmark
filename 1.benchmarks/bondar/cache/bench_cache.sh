#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <LOG_FILE>"
    exit 1
fi

LOG_FILE="$1"
MIN_SIZE=1024        # Minimum size in integers
MAX_SIZE=16777216    # Maximum size in integers
FACTOR=1.1           # Growth factor for sizes
ITERATIONS=20        # Number of times to run each benchmark

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
        out=$(taskset -c 1 ./measure "$current_size" "$K")
        sleep 0.1
        echo "$out"
        read_ops_sec=$(echo "$out" | awk '{print $8}')
        write_ops_sec=$(echo "$out" | awk '{print $16}')

        read_results+=($read_ops_sec)
        write_results+=($write_ops_sec)
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

    median_read=$(calculate_median "${read_results[@]}")
    median_write=$(calculate_median "${write_results[@]}")
    
    echo "READ: MEDIAN ${median_read}"
    echo "WRITE: MEDIAN ${median_write}"
    echo "------------------------------------------------------------"

    echo "$current_size $median_read $median_write" >> "$LOG_FILE"

    current_size=$(awk -v cs="$current_size" -v factor="$FACTOR" 'BEGIN {printf "%d", cs*factor}')
done
