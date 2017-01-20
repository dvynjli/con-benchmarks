
CPPFLAGS=
CFLAGS=-Wall -pthread -g
CC=clang
LDLIBS=

#T=svc16_lazy01_false-unreach-call
#T=svc16_sigma_false-unreach-call
#T=svc16_stateful01_true-unreach-call
#T=atgc-count
#T=threadpool
T=sorting
#T=findmax

S=$(wildcard *.c)
O=$(S:.c=)

all : $O

run :
	./$T

clean :
	rm -f $O *.o
