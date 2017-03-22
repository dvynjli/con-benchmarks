#!/bin/bash
# 
# programs with acyclic state spaces
echo "yogar-cbmc (atgc-count):"; date;
{ echo "yogar-cbmc (atgc-count):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc atgc-count.c; } &> log/yogar-cbmc/atgc-count.log
echo "yogar-cbmc (atgc-count_3):"; date;
{ echo "yogar-cbmc (atgc-count_3):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc atgc-count_3.c; } &> log/yogar-cbmc/atgc-count_3.log
echo "yogar-cbmc (atgc-count_4):"; date;
{ echo "yogar-cbmc (atgc-count_4):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc atgc-count_4.c; } &> log/yogar-cbmc/atgc-count_4.log
echo "yogar-cbmc (svc16_lazy01_true-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_lazy01_true-unreach-call):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_lazy01_true-unreach-call.c; } &> log/yogar-cbmc/svc16_lazy01_true-unreach-call.log
echo "yogar-cbmc (svc16_lazy01_false-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_lazy01_false-unreach-call):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_lazy01_false-unreach-call.c; } &> log/yogar-cbmc/svc16_lazy01_false-unreach-call.log
echo "yogar-cbmc (svc16_sigma_false-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_sigma_false-unreach-call):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_sigma_false-unreach-call.c; } &> log/yogar-cbmc/svc16_sigma_false-unreach-call.log
echo "yogar-cbmc (svc16_sigma_true-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_sigma_true-unreach-call):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_sigma_true-unreach-call.c; } &> log/yogar-cbmc/svc16_sigma_true-unreach-call.log
echo "yogar-cbmc (svc16_stateful01_true-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_stateful01_true-unreach-call):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_stateful01_true-unreach-call.c; } &> log/yogar-cbmc/svc16_stateful01_true-unreach-call.log

echo "yogar-cbmc (svc16_lazy01_true-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_lazy01_true-unreach-call):"; timeout 1h time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_lazy01_true-unreach-call.c; } &> log/yogar-cbmc/svc16_lazy01_true-unreach-call.log
echo "yogar-cbmc (svc16_lazy01_false-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_lazy01_false-unreach-call):"; timeout 1h time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_lazy01_false-unreach-call.c; } &> log/yogar-cbmc/svc16_lazy01_false-unreach-call.log
echo "yogar-cbmc (svc16_sigma_false-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_sigma_false-unreach-call):"; timeout 1h time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_sigma_false-unreach-call.c; } &> log/yogar-cbmc/svc16_sigma_false-unreach-call.log
echo "yogar-cbmc (svc16_sigma_true-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_sigma_true-unreach-call):"; timeout 1h time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_sigma_true-unreach-call.c; } &> log/yogar-cbmc/svc16_sigma_true-unreach-call.log
echo "yogar-cbmc (svc16_stateful01_true-unreach-call):"; date;
{ echo "yogar-cbmc (svc16_stateful01_true-unreach-call):"; timeout 1h time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc svc16_stateful01_true-unreach-call.c; } &> log/yogar-cbmc/svc16_stateful01_true-unreach-call.log
#
## programs with non-acyclic state spaces
echo "yogar-cbmc (sorting):"; date;
{ echo "yogar-cbmc (sorting):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc sorting.c ; } &>  log/yogar-cbmc/sorting.log
echo "yogar-cbmc (sorting_3):"; date;
{ echo "yogar-cbmc (sorting_3):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc sorting_3.c ; } &> log/yogar-cbmc/sorting_3.log
echo "yogar-cbmc (sorting_4):"; date;
{ echo "yogar-cbmc (sorting_4):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc sorting_4.c ; } &> log/yogar-cbmc/sorting_4.log

echo "yogar-cbmc (threadpool):"; date;
{ echo "yogar-cbmc (threadpool):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc threadpool.c ; } &> log/yogar-cbmc/threadpool.log

echo "yogar-cbmc (findmax):"; date;
{ echo "yogar-cbmc (findmax):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax.c ; } &> log/yogar-cbmc/findmax.log
echo "yogar-cbmc (findmax_3q_3i):"; date;
{ echo "yogar-cbmc (findmax_3q_3i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_3q_3i.c ; } &> log/yogar-cbmc/findmax_3q_3i.log
echo "yogar-cbmc (findmax_4q_3i):"; date;
{ echo "yogar-cbmc (findmax_4q_3i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_4q_3i.c ; } &> log/yogar-cbmc/findmax_4q_3i.log
echo "yogar-cbmc (findmax_5q_3i):"; date;
{ echo "yogar-cbmc (findmax_5q_3i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_5q_3i.c ; } &> log/yogar-cbmc/findmax_5q_3i.log

echo "yogar-cbmc (findmax_2q_4i):"; date;
{ echo "yogar-cbmc (findmax_2q_4i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_2q_4i.c ; } &> log/yogar-cbmc/findmax_2q_4i.log
echo "yogar-cbmc (findmax_3q_4i):"; date;
{ echo "yogar-cbmc (findmax_3q_4i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_3q_4i.c ; } &> log/yogar-cbmc/findmax_3q_4i.log
echo "yogar-cbmc (findmax_4q_4i):"; date;
{ echo "yogar-cbmc (findmax_4q_4i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_4q_4i.c ; } &> log/yogar-cbmc/findmax_4q_4i.log
echo "yogar-cbmc (findmax_5q_4i):"; date;
{ echo "yogar-cbmc (findmax_5q_4i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_5q_4i.c ; } &> log/yogar-cbmc/findmax_5q_4i.log

echo "yogar-cbmc (findmax_2q_5i):"; date;
{ echo "yogar-cbmc (findmax_2q_5i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_2q_5i.c ; } &> log/yogar-cbmc/findmax_2q_5i.log
echo "yogar-cbmc (findmax_3q_5i):"; date;
{ echo "yogar-cbmc (findmax_3q_5i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_3q_5i.c ; } &> log/yogar-cbmc/findmax_3q_5i.log
echo "yogar-cbmc (findmax_4q_5i):"; date;
{ echo "yogar-cbmc (findmax_4q_5i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_4q_5i.c ; } &> log/yogar-cbmc/findmax_4q_5i.log
echo "yogar-cbmc (findmax_5q_5i):"; date;
{ echo "yogar-cbmc (findmax_5q_5i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_5q_5i.c ; } &> log/yogar-cbmc/findmax_5q_5i.log

echo "yogar-cbmc (findmax_2q_6i):"; date;
{ echo "yogar-cbmc (findmax_2q_6i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_2q_6i.c ; } &> log/yogar-cbmc/findmax_2q_6i.log
echo "yogar-cbmc (findmax_3q_6i):"; date;
{ echo "yogar-cbmc (findmax_3q_6i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_3q_6i.c ; } &> log/yogar-cbmc/findmax_3q_6i.log
echo "yogar-cbmc (findmax_4q_6i):"; date;
{ echo "yogar-cbmc (findmax_4q_6i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_4q_6i.c ; } &> log/yogar-cbmc/findmax_4q_6i.log
echo "yogar-cbmc (findmax_5q_6i):"; date;
{ echo "yogar-cbmc (findmax_5q_6i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_5q_6i.c ; } &> log/yogar-cbmc/findmax_5q_6i.log

echo "yogar-cbmc (findmax_2q_7i):"; date;
{ echo "yogar-cbmc (findmax_2q_7i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_2q_7i.c ; } &> log/yogar-cbmc/findmax_2q_7i.log
echo "yogar-cbmc (findmax_3q_7i):"; date;
{ echo "yogar-cbmc (findmax_3q_7i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_3q_7i.c ; } &> log/yogar-cbmc/findmax_3q_7i.log
echo "yogar-cbmc (findmax_4q_7i):"; date;
{ echo "yogar-cbmc (findmax_4q_7i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_4q_7i.c ; } &> log/yogar-cbmc/findmax_4q_7i.log
echo "yogar-cbmc (findmax_5q_7i):"; date;
{ echo "yogar-cbmc (findmax_5q_7i):"; timeout 30m time ./yogar-cbmc --no-unwinding-assertions --32 --mm sc findmax_5q_7i.c ; } &> log/yogar-cbmc/findmax_5q_7i.log

