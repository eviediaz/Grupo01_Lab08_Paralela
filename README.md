First attempt:

```
$ ./main_bm 
2024-10-14T23:25:14+02:00
Running ./main_bm
Run on (16 X 4600 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 24576 KiB (x1)
Load Average: 1.84, 1.60, 1.19
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
--------------------------------------------------------------------------
Benchmark                                Time             CPU   Iterations
--------------------------------------------------------------------------
BM_secuencial/real_time               53.5 ms         53.5 ms           11
BM_estandar/real_time                 77.7 ms        0.438 ms            9
BM_estandar_reduction/real_time       4.22 ms        0.417 ms          165
BM_openmp_atomic/real_time            1773 ms         1679 ms            1
BM_openmp_reduction/real_time         15.3 ms         14.8 ms           56
BM_openmp_lock_guard/real_time        9381 ms         8329 ms            1
BM_openmp_lock_unlock/real_time       9665 ms         8511 ms            1
BM_openmp_critical/real_time         14150 ms         8383 ms            1
BM_openmp_ompatomic/real_time         1882 ms         1594 ms            1
```