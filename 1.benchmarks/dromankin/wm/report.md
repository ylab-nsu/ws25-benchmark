# Watermark benchmark

Поступила просьба от команды Watermark протестировать следующие инструкции:

```
c.nop
c.or x0, x0
c.andi x0, 0b011111
c.sub x0, x0
```

Однако выяснилось, что последние три операции работают только с регистрами x8 - x15, поэтому замеры проводились только для `c.nop`


Горячий код:
![hotcode.png](images/hotcode.png)


Скрипт просмотра горячего кода:

```bash
#!/bin/bash
cd ../
gcc  -fno-verbose-asm -march=rv64idc wm_bench.c -o wm_bench -O0 -pg
perf record -e cpu-clock ./wm_bench $1 $2
perf report
```
Скрипт запуска бенчмарка:

```bash
#!/bin/bash
gcc  -fno-verbose-asm -march=rv64idc wm_bench.c -o wm_bench -O0 -pg
rep=20
iter=100000
n=10000000

for ((i = 1; i < $n + 1; i+=$iter))
do
perf stat -o out.txt -r $rep --table ./wm_bench $i
grep ") #" out.txt > out2.txt
cat out2.txt | cut -d"(" -f1 >> out3.txt
done
```

Программа для построения графиков:
```python
import matplotlib.pyplot as plt
import numpy as np
import sys

CONST = int(sys.argv[1])
file = open("out3.txt", "r")
file2 = open("banana_out3.txt", "r")
x = []
y = []
y2 = []
buf = []
min_val = 0
count = 1
c = 0

for line in file:
	buf.append(float(line))
	c += 1
	if c == CONST:
		min_val = min(buf)
		y.append(min_val)
		x.append(count)
		count += 1000000
		c = 0
		buf = []
buf = []
c = 0
min_val = 0
for line in file2:
	buf.append(float(line))
	c += 1
	if c == CONST:
		min_val = min(buf)
		y2.append(min_val)
		c = 0

		buf = []


plt.figure().set_figwidth(15)
plt.plot(x, y, 'ro-', label='lichee')
plt.plot(x, y2, 'go-', label='banana')
plt.title("c.nop", fontsize = 20)
plt.grid(True)
plt.ylabel('time(s)', fontsize = 15)
plt.xlabel('operations', fontsize = 15)

plt.ylim([0, 1])
plt.legend()
plt.savefig('out_cnop.png')
file.close()
file2.close()
```

Запуск: `./bench.sh <кол-во циклов>` (для функций с ассемблерными вставками - `bench_asm.sh`)

Скрипт создаёт файлы вида `<имя_платы>_out3.txt`.
Файлы с платы Lichee должны иметь вид `out3.txt`, с Banana - `banana_out3.txt`.

Эти файлы нужны для запуска программы построения графиков `test.py`

Запуск: `python test.py <значение переменной rep в скрипте для замеров>`

Например: `python test.py 20`

Переменная `rep` - количество запусков на некотором значении количества операций, среди которых выбирается минимальное

Примечание: для запуска нужна библиотека `matplotlib`

## Результаты бенчмарка

![out3.png](images/out3.png)