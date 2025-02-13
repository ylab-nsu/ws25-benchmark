# Бенчмарки на измерение Cache Bandwidth и Cache Latency (Второй отчет)

Данный отчет - продолжение [первой части](./sort_benchmark.md).

Во второй части описываются бенчмарки, целью которых было измерение Cache Bandwidth и Cache Latency.

## Цель

Изначально целью второй части работы было измерение Cache Latency.

Но в качестве прериквизита к измерению Latency было решено измерит Memory Bandwidth, что в конечном итоге оказалось ощутимо сложнее.

## Методология

Для проведения бенчмарков использовались 2 разных подхода:

- **Sequential Memory Access** - алгоритм читает/пишет данные в последовательной и предсказуемой манере.
- **Pointer Chasing** - данный алгоритм проходится по рандомно связнному связному списку и тем самый каждый доступ к памяти зависит от предыдущего, что делает невозможным предсказание следующего доступа hardware prefetcher-ом.

    Позволяет изучить настоящие значения Bandwidth/Latency не искаженные работой prefetcher-а.

Пример Pointer Chasing алгоритма:

```C
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t t = 0; t < K*N; t++) {
            p->value = sink;
            p = p->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
```

Для измерения времения использовался `clock_gettime`.

Заране стоит упомянуть параметры систем памяти наших плат:

**Lichee:**

```text
The L1 data memory system has the following features:
- 64 kB I-Cache & D-Cache
- PIPT, two-way set associative L1 data cache.
- Fixed cache line length of 64 bytes.
- 128-bit read interface from the L2 memory system.
- Up to 128-bit read data paths from the data L1 memory system to the data path.
- Up to 128-bit write data path from the data path to the L1 memory system.

The L2 Cache has the following features:
- Configurable size of 256KB, 512KB, 1MB, 2MB, 4MB, or 8MB. (1MB in our case)
- PIPT, 16-way set-associative structure.
- Fixed line length of 64 bytes.
- Optional ECC protection.
- Support data prefetch.
```

Источники:
[T-HEAD XuanTie C910 RISC-V](https://www.riscvschool.com/2023/03/09/t-head-xuantie-c910-risc-v/)

**Banana:**

```text
The L1 data memory system has the following features:
- 32 kB I-Cache & D-Cache
- L1 Cache supports MESI consistency protocol
- 64 bytes line size 
- 4-way associative

The L2 Cache has the following features:
- 512 kB per cluster (4 cores)
- 0 cluster have additional 512 kB TCM memory
- L2 Cache supports MOESI consistency protocol
- 64 bytes line size
- 16-way associative
```

Источники:
[Banana Pi BPI-F3 SpacemiT K1 RISC-V chip datasheet](https://docs.banana-pi.org/en/BPI-F3/SpacemiT_K1_datasheet)

[K1 developer documentation](https://developer.spacemit.com/documentation?token=BWbGwbx7liGW21kq9lucSA6Vnpb)

## Инструменты

Общий набор инструментов остался аналогичным первой части работы ([Раздел Инструменты](./sort_benchmark.md)).

Изменения коснулись двух аспектов:

- Вместо флага компиляции `-O0` использовался флаг `-O3`, включающий оптимизации, для получения настоящих значений Bandwidth и Latency.
- Были написанны новые Bash-скрипты для автоматизации бенчмарков.

    Исходный код: [bench_cache.sh](/1.benchmarks/bondar/cache/bench_cache.sh)

    Исходный код: [bench_latency.sh](/1.benchmarks/bondar/cache/bench_latency.sh)

## Результаты исследования

### Первый результат

![First result](./../../1.benchmarks/bondar/cache/pics/pointer_Chase_1_try.svg)

В коде для write бенчмарка была допущенна ошибка, которая делала доступ к памяти последовательным, что в теории должно было испортить данные (как мы увидим далее).

```C
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t t = 0; t < K; t++) {
        for (size_t i = 0; i < N; i++) {
            nodes[i] = sink;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Правильный Pointer Chasing:

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t t = 0; t < K*N; t++) {
            p->value = sink;
            p = p->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
```

Но мы получили на удивление красивый и гладкий график.

### Финальный результат

![Final Lichee vs Banana Read](./../../1.benchmarks/bondar/cache/pics/Lichee_vs_Banana_read.svg)

![Final Lichee vs Banana Write](./../../1.benchmarks/bondar/cache/pics/Lichee_vs_Banana_write.svg)

После исправления ошибки и использования медианы для сбора данных(также на каждое N теперь берется по 20 прогонов) были получены финальные данные.

Данные не такие красивые, но отображают общую тенденцию на снижение пропускной способности при переходе на L2 кэш.

Заметно, что операции записи и на Lichee и на Banana имеют примерно одинаковую пропускную способность, но вот операции записи быстрее на Banana(пока мы находимся в L1 кэше).

Также заметно снижение пропускной способности при переходе с L2 кэша на Main Memory, но это снижение не такое кардинальное, как ожидается (только в 2-3 раза).

Исходный код: [cache_bandwidth_pointer_chase.c](/1.benchmarks/bondar/cache/cache_bandwidth_pointer_chase.c)

### Последовательный доступ к памяти

![Sequential Acces 1](./../../1.benchmarks/bondar/cache/pics/Sequential.svg)

![Sequential Acces 2](./../../1.benchmarks/bondar/cache/pics/Sequential_2.svg)

Самые интересные эффекты наблюдаются при использовании sequential доступа к памяти.

Исходный код: [cache_bandwidth_sequential.c](/1.benchmarks/bondar/cache/cache_bandwidth_sequential.c)

Первый график не совсем корректен, потому что при прогонах данного теста переменная, используемая для операций чтения/записи была не `volatile`, что привело к оптимизациям компилятором нашего цикла.

Как мы видим на финальном графике:

- Пока мы находимся в L1 кэше операции чтения и записи держатся примерно на одном уровне (при этом пропускная способность чтения выше), помимо больших шумов и скачков на операциях записи
- при переходе на L2 кэш мы наблюдаем постепенный рост пропускной способности, который по итогу также выходит на плато и превышает по своему значения пропускную способность в L1 кэше.

Последнее наблюдение очень парадаксально, так как L2 кэш оказывается быстрее с точки зрения пропускной способности чем L1 кэш.

Основной причиной подобного поведения может ялвятся поведение Prefetcher-а CPU:

- В [спецификации](https://www.riscvschool.com/2023/03/09/t-head-xuantie-c910-risc-v/) ядер, которые используются на плате Lichee явно не указано, отсутствие Prefetcher-а в L1 кэше, но всё указывает на это.
- Наличие Prefetcher-а в L2 кэше явно указано в спецификации.

    По мере повторения цикла Prefetcher становится более эффективным, заранее подгружая данные наперед и уменьшая кол-во stall cycles, что увеличивает эффективную memory bandwidth.

> Конечно, Prefetcher это мощный инструмент и он может служуть причиной наблюдаемого эффекта. Но все-же достаточно странным является превосходство L2 кеша над L1 кэшом по пропускной способности(при выходе на плато). Так как, не смотря на эффективность работы Prefetcher-а совмещенной с последовательным доступом к памяти, L1 кэш физически находится ближе к процессору и имеет более широкую полосу пропускания данных (правда стоит заметить, что в спецификации не указана ширина полосы для L2 кэша, только для L1).

### Сравнения int и long long

![Int vs long long Read](./../../1.benchmarks/bondar/cache/pics/int_vs_long_read_2.svg)

![Int vs long long Write](./../../1.benchmarks/bondar/cache/pics/int_vs_long_write_2.svg)

Исходный код: [cache_bandwidth_longlong.c](/1.benchmarks/bondar/cache/cache_bandwidth_longlong.c)

... немного

### Cycles count (??????)

![Cycles count k=10](./../../1.benchmarks/bondar/cache/pics/pointer_chase_k_10.svg)

![Cycles count k=1000](./../../1.benchmarks/bondar/cache/pics/pointer_chase_k_1000.svg)

немного

### Измерение Latency

![Latency Lichee vs Banana](./../../1.benchmarks/bondar/cache/pics/Latency.svg)

немного

- про ошибку

Исходный код: [latency.c](/1.benchmarks/bondar/cache/latency.c)

## How to reproduce benchmarks

1. Bandwidth
2. Latency

## Заключение

кратко

## Будущая работа

- influence of optimization
- hacks (alibaba ...)
- try to measure latency with sequential
