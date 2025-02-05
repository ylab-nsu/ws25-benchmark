perf record -e cpu-clock ./main_asm $1 $2
perf report
