# FMA benchmark

Бенчмарк направлен на тестирование операций FMA (Fused-Multiply Add, умножение-сложение): fmadd и fmsub на разных платах в двух вариантах: как функция на языке C и как ассемблерная инструкция (с помощью ассемблерных вставок)
Платы: LicheePi 4A; Banana Pi BPI-F3

Lichee
```
4 cores

cpu-freq        : 1.848Ghz
cpu-icache      : 64KB
cpu-dcache      : 64KB
cpu-l2cache     : 1MB
cpu-tlb         : 1024 4-ways
cpu-cacheline   : 64Bytes
cpu-vector      : 0.7.1
```
Banana
```
8 cores

CPU(s) scaling MHz:  100%
  CPU max MHz:         1600.0000
  CPU min MHz:         614.4000
Caches (sum of all):
  L1d:                 256 KiB (8 instances)
  L1i:                 256 KiB (8 instances)
  L2:                  1 MiB (2 instances)
LEVEL1_ICACHE_SIZE                 32768
LEVEL1_ICACHE_ASSOC                4
LEVEL1_ICACHE_LINESIZE             64
LEVEL1_DCACHE_SIZE                 32768
LEVEL1_DCACHE_ASSOC                4
LEVEL1_DCACHE_LINESIZE             64
LEVEL2_CACHE_SIZE                  524288
LEVEL2_CACHE_ASSOC                 16
LEVEL2_CACHE_LINESIZE              64
LEVEL3_CACHE_SIZE                  0
LEVEL3_CACHE_ASSOC                 0
LEVEL3_CACHE_LINESIZE              0
LEVEL4_CACHE_SIZE                  0
LEVEL4_CACHE_ASSOC                 0
LEVEL4_CACHE_LINESIZE              0
```

Основное тело цикла:
```c
double fmadd(int32_t marg, volatile double darg, double aarg, double barg,
             double carg) {
    for (int32_t i = 0; i < marg; i++) {
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
        darg = aarg + barg * carg;
    }
    return darg;
}
```
Ассемблерная инструкция:
```c
double fmadd(int32_t marg, volatile double darg, double aarg, double barg,
             double carg) {
    for (int32_t i = 0; i < marg; i++) {
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
        asm volatile("fmadd.d %0, %1, %2, %3"
                     : "=f"(darg)
                     : "f"(barg), "f"(carg), "f"(aarg));
    }
    return darg;
}
```
(аналогично для fmadd)

Дублирование кода инструкций в теле циклов необходимо для того, чтобы наиболее "горячими" были инструкции, действительно относящиеся к функции (т.н. loop unrolling) (в данном случае - `fadd.d` и `fsub.d`).

Рассмотрим на примере функции fmadd:
Так выглядит профилировка с одной операцией сложения в цикле:

![sextw_lw_hotspot.png](images/sextw_lw_hotspot.png)

Видно, что большую часть работы занимают инструкции `sext.w` и `lw`, в то время как нужные нам инструкции `fadd.s` и `fmul.s` занимают менее 9% от всего времени работы

Если же продублировать операцию сложения:

![sextw_lw_hotspot_after.png](images/sextw_lw_hotspot_after.png)

Инструкции `sext.w` и `lw` выполняются меньшее кол-во времени, а инструкции сложения и умножения в сумме занимают ~77%, поэтому такой код можно использовать для тестирования

Горячий код (с ассемблерными вставками) (~92%):

![asm_hotspot.png](images/asm_hotspot.png)


## Окружение:
* Сборка и ключи компиляции
```
gcc -g main.c -o main -O0 -pg

gcc  -fno-verbose-asm -march=rv64id main_asm.c -o main_asm -O3 -pg
```
Ключи `-g`, `-pg` и `-fno-verbose-asm` создают дополнительную информацию, полезную при профилировке и отладке (`-pg`, в частности, создаёт `gmon.out` для профилировщика `gprof`)
Ключ `-O` устанавливает степень оптимизации компилятора
Ключ `-march=rv64id` подключает расширение RISC-V для работы c double
* Скрипт для просмотра горячего кода (аналогично для бенчмарка с ассемблерными вставками)
```bash
cd ../
perf record -e cpu-clock ./main $1 $2
perf report
```


* Скрипт для замеров и записи значений в отдельный файл (аналогично для бенчмарка с ассемблерными вставками)
```bash
cd ../
rep=20
iter=100000
n=10000000
gcc -g main.c -o main -O0 -pg
if [[ $1 == 1 ]]; then
	for ((i = 1; i < $n + 1; i+=$iter))
	do
	perf stat -o out_fmadd.txt -r $rep --table ./main $1 $i
	grep ") #" out_fmadd.txt > out2_fmadd.txt
	cat out2_fmadd.txt | cut -d"(" -f1 >> out3_fmadd.txt
	done
else
	for ((i = 1; i < $n + 1; i+=$iter))
	do
	perf stat -o out_fmsub.txt -r $rep --table ./main $1 $i
	grep ") #" out_fmsub.txt > out2_fmsub.txt
	cat out2_fmsub.txt | cut -d"(" -f1 >> out3_fmsub.txt
	done
fi
```
Запуск: ./parse.sh <номер функции: 1 - fmadd, 2 - fmsub>

Скрипт создаёт файлы вида out3_<имя_функции>_<ассемблер>.txt.
Файлы с платы Lichee должны иметь вид out3_fmadd.txt, с Banana - banana_out3_fmadd.txt.

Эти файлы нужны для запуска программы построения графиков `test.py`

Запуск: python test.py <значение переменной rep в скрипте для замеров>

Например: python test.py 20
## Результаты работы бенчмарка

# Fmadd
![out_fmadd.png](images/out_fmadd.png)
# Fmadd(ассемблер)
![out_fmadd_asm.png](images/out_fmadd_asm.png)
# Fmsub
![out_fmsub.png](images/out_fmsub.png)
# Fmsub(ассемблер)
![out_fmsub_asm.png](images/out_fmsub_asm.png)