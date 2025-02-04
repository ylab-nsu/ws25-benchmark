perf record -e cpu-clock ./main $1
perf report
