#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <M> <LOG_FILE>"
    exit 1
fi

M="$1"
LOG_FILE="$2"

M2=$M*2
read -a Ns < input.txt

for N in "${Ns[@]}"; do
    echo ">>> For N = $N:"
    
    taskset -c 1 ./sort "$M2" "$N" &
    pid=$!
    
    sleep 0.001

    vmrss=$(awk '/VmRSS/ {print $2, $3}' /proc/$pid/status)
    echo "    Memory usage (VmRSS): $vmrss"
    
    wait $pid
    
    out=$(taskset -c 1 perf stat -e cache-misses,context-switches,task-clock -r 10 ./sort "$M" "$N" 2>&1 >/dev/null)
    
    task_clock_line=$(echo "$out" | awk '/task-clock/ {print}')
    task_clock=$(echo "$task_clock_line" | awk '{print $1}')
    
    context_switch_line=$(echo "$out" | awk '/context-switches/ {print}')
    context_switches=$(echo "$context_switch_line" | awk '{print $1}')
    
    cache_miss_line=$(echo "$out" | awk '/cache-misses/ {print}')
    cache_misses=$(echo "$cache_miss_line" | awk '{print $1}')
    
    echo "    task-clock:        $task_clock msec"
    echo "    context-switches:  $context_switches"
    echo "    cache-misses:      $cache_misses"
    
    # Format: N TaskClock VmRSS ContextSwitches CacheMisses
    echo "$N $task_clock $vmrss $context_switches $cache_misses" >> "$LOG_FILE"
done
