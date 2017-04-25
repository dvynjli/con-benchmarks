#!/bin/bash

# benchmarks
declare -a bench=("atgc" "atgc_3" "atgc_4" "cond" "lazy_true" "lazy_false" "monab_1" "monab_2" "rand" "sigma_false" "sigma_true" "stf" "fmax_2q_4i.c" "fmax_2q_7i.c" "fmax_4q_6i.c" "fmax_5q_3i.c" "tpoll_3.c"  "tpoll.c" "fmax_2q_6i.c" "fmax_3q_3i.c" "fmax_4q_7i.c" "fmax.c" "thpool.c" "tpoll_4.c") 

## run cbmc 
for i in "${acy[@]}"
do
   echo "cbmc $i"
   timeout 30m time ./cbmc --no-unwinding-assertions --32 --mm sc --unwind 5 $i.c &> log/cbmc/$i.log 
done
 
## run impara 
for i in "${nacy[@]}"
do
   echo "impara $i"
   timeout 30m time ./impara $i.c &> log/impara/$i.log 
done
