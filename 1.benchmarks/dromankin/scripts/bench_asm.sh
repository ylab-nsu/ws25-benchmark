for ((i = 1; i < 1000000 + 1; i+=1000))
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
