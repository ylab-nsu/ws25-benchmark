cd ../
gcc  -fno-verbose-asm -march=rv64id main_asm.c -o main_asm -O0 -pg
for ((i = 1; i < 10000000 + 1; i+=100000))
do
if [[ $1 == 1 ]] then
	perf stat -o out.txt  ./main_asm $1 $i
	grep elapsed out.txt > out2.txt
	cat out2.txt | cut -d"s" -f1 >> out3fmadd_asm.txt
else
	perf stat -o out.txt  ./main_asm $1 $i
	grep elapsed out.txt > out2.txt
	cat out2.txt | cut -d"s" -f1 >> out3fmsub_asm.txt
fi
done
