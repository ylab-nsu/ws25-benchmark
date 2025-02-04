perf record -e cpu-clock ./main_asm $1
perf report
