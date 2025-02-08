cd ../
perf record -e cpu-clock ./main $1 $2
perf report
