#!/bin/bash
# 
# programs with acyclic state spaces
echo "poet (atgc-count):"; date;
{ echo "poet (atgc-count, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=atgc-count.c; } &>  log/atgc-count.log
echo "poet (atgc-count_3):"; date;
{ echo "poet (atgc-count_3, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=atgc-count_3.c; } &>  log/atgc-count_3.log
echo "poet (atgc-count_4):"; date;
{ echo "poet (atgc-count_4, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=atgc-count_4.c; } &>  log/atgc-count_4.log
echo "poet (laz01_false):"; date;
{ echo "poet (svc16_lazy01_false-unreach-call, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_lazy01_false-unreach-call.c; } &>  log/svc16_lazy01_false-unreach-call.log
echo "poet (laz01_true):"; date;
{ echo "poet (svc16_lazy01_true-unreach-call, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_lazy01_true-unreach-call.c; } &>  log/svc16_lazy01_true-unreach-call.log
echo "poet (sigma_false):"; date;
{ echo "poet (svc16_sigma_false-unreach-call, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_sigma_false-unreach-call.c; } &>  log/svc16_sigma_false-unreach-call.log
echo "poet (sigma_true):"; date;
{ echo "poet (svc16_sigma_true-unreach-call, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_sigma_true-unreach-call.c; } &>  log/svc16_sigma_true-unreach-call.log
echo "poet (stateful):"; date;
{ echo "poet (svc16_stateful01_true-unreach-call, cutoff=n):"; timeout 30m time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_stateful01_true-unreach-call.c; } &>  log/svc16_stateful01_true-unreach-call.log
#
## programs with non-acyclic state spaces
echo "poet (findmax):"; date;
{ echo "poet (findmax-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax-poet.c; } &>  log/findmax-poet.log
echo "poet (findmax 2 4):"; date;
{ echo "poet (findmax_2q_4i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_2q_4i-poet.c; } &>  log/findmax_2q_4i-poet.log
echo "poet (findmax 2 5):"; date;
{ echo "poet (findmax_2q_5i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_2q_5i-poet.c; } &>  log/findmax_2q_5i-poet.log
echo "poet (findmax 2 6):"; date;
{ echo "poet (findmax_2q_6i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_2q_6i-poet.c; } &>  log/findmax_2q_6i-poet.log
echo "poet (findmax 2 7):"; date;
{ echo "poet (findmax_2q_7i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_2q_7i-poet.c; } &>  log/findmax_2q_7i-poet.log
echo "poet (findmax 3 3):"; date;
{ echo "poet (findmax_3q_3i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_3q_3i-poet.c; } &>  log/findmax_3q_3i-poet.log
echo "poet (findmax 3 4):"; date;
{ echo "poet (findmax_3q_4i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_3q_4i-poet.c; } &>  log/findmax_3q_4i-poet.log
echo "poet (findmax 3 5):"; date;
{ echo "poet (findmax_3q_5i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_3q_5i-poet.c; } &>  log/findmax_3q_5i-poet.log
echo "poet (findmax 3 6):"; date;
{ echo "poet (findmax_3q_6i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_3q_6i-poet.c; } &>  log/findmax_3q_6i-poet.log
echo "poet (findmax 3 7):"; date;
{ echo "poet (findmax_3q_7i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_3q_7i-poet.c; } &>  log/findmax_3q_7i-poet.log
echo "poet (findmax 4 3):"; date;
{ echo "poet (findmax_4q_3i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_4q_3i-poet.c; } &>  log/findmax_4q_3i-poet.log
echo "poet (findmax 4 4):"; date;
{ echo "poet (findmax_4q_4i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_4q_4i-poet.c; } &>  log/findmax_4q_4i-poet.log
echo "poet (findmax 4 5):"; date;
{ echo "poet (findmax_4q_5i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_4q_5i-poet.c; } &>  log/findmax_4q_5i-poet.log
echo "poet (findmax 4 6):"; date;
{ echo "poet (findmax_4q_6i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_4q_6i-poet.c; } &>  log/findmax_4q_6i-poet.log
echo "poet (findmax 4 7):"; date;
{ echo "poet (findmax_4q_7i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_4q_7i-poet.c; } &>  log/findmax_4q_7i-poet.log
echo "poet (findmax 5 3):"; date;
{ echo "poet (findmax_5q_3i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_5q_3i-poet.c; } &>  log/findmax_5q_3i-poet.log
echo "poet (findmax 5 4):"; date;
{ echo "poet (findmax_5q_4i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_5q_4i-poet.c; } &>  log/findmax_5q_4i-poet.log
echo "poet (findmax 5 5):"; date;
{ echo "poet (findmax_5q_5i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_5q_5i-poet.c; } &>  log/findmax_5q_5i-poet.log
echo "poet (findmax 5 6):"; date;
{ echo "poet (findmax_5q_6i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_5q_6i-poet.c; } &>  log/findmax_5q_6i-poet.log
echo "poet (findmax 5 7):"; date;
{ echo "poet (findmax_5q_7i-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=findmax_5q_7i-poet.c; } &>  log/findmax_5q_7i-poet.log
echo "poet (tpoll):"; date;
{ echo "poet (tpoll-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=tpoll-poet.c; } &>  log/tpoll-poet.log
echo "poet (tpoll 3):"; date;
{ echo "poet (tpoll_3-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=tpoll_3-poet.c; } &>  log/tpoll_3-poet.log
echo "poet (tpoll 4):"; date;
{ echo "poet (tpoll_4-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=tpoll_4-poet.c; } &>  log/tpoll_4-poet.log
echo "poet (threadpool):"; date;
{ echo "poet (threadpool-poet, cutoff=y):"; timeout 30m time poet explore -d=Interval -s=0 -c=1 -w=15 -i=threadpool-poet.c; } &>  log/threadpool-poet.log
