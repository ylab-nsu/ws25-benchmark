cd ../
gcc -g main.c -o main -O0 -pg
for ((i = 1; i < 10000000 + 1; i+=100000))
do
if [[ $1 == 1 ]]; then
        perf stat -o outfmadd.txt  ./main $1 $i
        grep elapsed outfmadd.txt > out2fmadd.txt
        cat out2fmadd.txt | cut -d"s" -f1 >> out3fmadd.txt
else
        perf stat -o outfmsub.txt  ./main $1 $i
        grep elapsed outfmsub.txt > out2fmsub.txt
        cat out2fmsub.txt | cut -d"s" -f1 >> out3fmsub.txt
fi
done
