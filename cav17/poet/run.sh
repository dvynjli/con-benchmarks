#!/bin/bash
# 
# programs with acyclic state spaces
{ echo "poet (atgc-count, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=atgc-count.c; } &>  log/atgc-count.log
{ echo "poet (atgc-count, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=atgc-count.c; } &>> log/atgc-count.log
{ echo "poet (atgc-count_3, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=atgc-count_3.c; } &>  log/atgc-count_3.log
{ echo "poet (atgc-count_3, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=atgc-count_3.c; } &>> log/atgc-count_3.log
#{ echo "poet (atgc-count_4, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=atgc-count_4.c; } &>  log/atgc-count_4.log
#{ echo "poet (atgc-count_4, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=atgc-count_4.c; } &>> log/atgc-count_4.log
#{ echo "poet (svc16_lazy01_false-unreach-call, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_lazy01_false-unreach-call.c; } &>  log/svc16_lazy01_false-unreach-call.log
#{ echo "poet (svc16_lazy01_false-unreach-call, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=svc16_lazy01_false-unreach-call.c; } &>> log/svc16_lazy01_false-unreach-call.log
#{ echo "poet (svc16_lazy01_true-unreach-call, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_lazy01_true-unreach-call.c; } &>  log/svc16_lazy01_true-unreach-call.log
#{ echo "poet (svc16_lazy01_true-unreach-call, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=svc16_lazy01_true-unreach-call.c; } &>> log/svc16_lazy01_true-unreach-call.log
#{ echo "poet (svc16_sigma_false-unreach-call, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_sigma_false-unreach-call.c; } &>  log/svc16_sigma_false-unreach-call.log
#{ echo "poet (svc16_sigma_false-unreach-call, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=svc16_sigma_false-unreach-call.c; } &>> log/svc16_sigma_false-unreach-call.log
#{ echo "poet (svc16_sigma_true-unreach-call, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_sigma_true-unreach-call.c; } &>  log/svc16_sigma_true-unreach-call.log
#{ echo "poet (svc16_sigma_true-unreach-call, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=svc16_sigma_true-unreach-call.c; } &>> log/svc16_sigma_true-unreach-call.log
#{ echo "poet (svc16_stateful01_true-unreach-call, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=svc16_stateful01_true-unreach-call.c; } &>  log/svc16_stateful01_true-unreach-call.log
#{ echo "poet (svc16_stateful01_true-unreach-call, cutoff=y):"; timeout 1h time poet explore -d=Interval -s=0 -c=1 -w=15 -i=svc16_stateful01_true-unreach-call.c; } &>> log/svc16_stateful01_true-unreach-call.log
#
## programs with non-acyclic state spaces
#{ echo "poet (findmax-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax-poet.c; } &>  log/findmax-poet.log
#{ echo "poet (findmax_2q_4i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_2q_4i-poet.c; } &>  log/findmax_2q_4i-poet.log
#{ echo "poet (findmax_2q_5i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_2q_5i-poet.c; } &>  log/findmax_2q_5i-poet.log
#{ echo "poet (findmax_2q_6i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_2q_6i-poet.c; } &>  log/findmax_2q_6i-poet.log
#{ echo "poet (findmax_2q_7i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_2q_7i-poet.c; } &>  log/findmax_2q_7i-poet.log
#{ echo "poet (findmax_2q_8i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_2q_8i-poet.c; } &>  log/findmax_2q_8i-poet.log
#{ echo "poet (findmax_3q_3i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_3q_3i-poet.c; } &>  log/findmax_3q_3i-poet.log
#{ echo "poet (findmax_3q_4i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_3q_4i-poet.c; } &>  log/findmax_3q_4i-poet.log
#{ echo "poet (findmax_3q_5i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_3q_5i-poet.c; } &>  log/findmax_3q_5i-poet.log
#{ echo "poet (findmax_3q_6i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_3q_6i-poet.c; } &>  log/findmax_3q_6i-poet.log
#{ echo "poet (findmax_3q_7i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_3q_7i-poet.c; } &>  log/findmax_3q_7i-poet.log
#{ echo "poet (findmax_3q_8i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_3q_8i-poet.c; } &>  log/findmax_3q_8i-poet.log
#{ echo "poet (findmax_4q_3i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_4q_3i-poet.c; } &>  log/findmax_4q_3i-poet.log
#{ echo "poet (findmax_4q_4i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_4q_4i-poet.c; } &>  log/findmax_4q_4i-poet.log
#{ echo "poet (findmax_4q_5i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_4q_5i-poet.c; } &>  log/findmax_4q_5i-poet.log
#{ echo "poet (findmax_4q_6i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_4q_6i-poet.c; } &>  log/findmax_4q_6i-poet.log
#{ echo "poet (findmax_4q_7i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_4q_7i-poet.c; } &>  log/findmax_4q_7i-poet.log
#{ echo "poet (findmax_4q_8i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_4q_8i-poet.c; } &>  log/findmax_4q_8i-poet.log
#{ echo "poet (findmax_5q_3i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_5q_3i-poet.c; } &>  log/findmax_5q_3i-poet.log
#{ echo "poet (findmax_5q_4i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_5q_4i-poet.c; } &>  log/findmax_5q_4i-poet.log
#{ echo "poet (findmax_5q_5i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_5q_5i-poet.c; } &>  log/findmax_5q_5i-poet.log
#{ echo "poet (findmax_5q_6i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_5q_6i-poet.c; } &>  log/findmax_5q_6i-poet.log
#{ echo "poet (findmax_5q_7i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_5q_7i-poet.c; } &>  log/findmax_5q_7i-poet.log
#{ echo "poet (findmax_5q_8i-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=findmax_5q_8i-poet.c; } &>  log/findmax_5q_8i-poet.log
#{ echo "poet (sorting-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=sorting-poet.c; } &>  log/sorting-poet.log
#{ echo "poet (sorting_3-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=sorting_3-poet.c; } &>  log/sorting_3-poet.log
#{ echo "poet (sorting_4-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=sorting_4-poet.c; } &>  log/sorting_4-poet.log
#{ echo "poet (threadpool-poet, cutoff=n):"; timeout 1h time poet explore -d=Interval -s=0 -c=0 -w=15 -i=threadpool-poet.c; } &>  log/threadpool-poet.log
