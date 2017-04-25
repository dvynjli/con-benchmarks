#!/bin/bash

# acyclic state spaces benchmarks
declare -a acy=("atgc" "atgc_3" "atgc_4" "cond" "lazy_true" "lazy_false" "monab_1" "monab_2" "rand" "sigma_false" "sigma_true" "stf")

# non-acyclic state spaces benchmarks
declare -a nacy=("fmax_2q_4i" "fmax_2q_7i" "fmax_4q_6i" "fmax_5q_3i" "tpoll_3"  "tpoll" "fmax_2q_6i" "fmax_3q_3i" "fmax_4q_7i" "fmax" "thpool" "tpoll_4") 

## run the acyclic benchmarks 
for i in "${acy[@]}"
do
   echo "apoet $i"
   timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=$i.c &> log/$i.log 
done
 
## run the non-acyclic benchmarks  (cutoffs are enabled)
for i in "${nacy[@]}"
do
   echo "apoet $i"
   timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=$i.c &> log/$i.log 
done
