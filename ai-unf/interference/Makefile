
U=$(shell id -nu)
H=$(shell hostname)

ifeq ($U-$H,cesar-polaris)
include ~/x/devel/poet/libc/inc.mk
endif

ifeq ($U-$H,msousa-??)
include ??? # inc.mk
endif


# generating full.c
#CPPFLAGS=$(POET_CPPFLAGS)
#CFLAGS=$(POET_CFLAGS) -Wall -pthread
#CC=$(POET_CC)
#LDLIBS=$(POET_LDLIBS_C)

# normal compilation
CPPFLAGS=-I .
CFLAGS=-Wall -pthread -g
CC=clang
LDLIBS=

FCROOT=~/x/devel/frama-c-Aluminium-20160501+dev
FC=$(FCROOT)/bin/frama-c
FFLAGS=-machdep x86_64 -no-unicode -slevel 1 -wlevel 20 -mt-verbose 2

PPC=cilly

#T=svc16_lazy01_false-unreach-call
#T=svc16_sigma_false-unreach-call
#T=svc16_stateful01_true-unreach-call
#T=atgc-count
#T=threadpool
T=sorting_4
#T=findmax
#T=findmax_5q_8i

S=$(wildcard *.c)
O=$(S:.c=)
X=$(S:.c=.o)

all : $X
	./$T

clean :
	rm -f $O *.o full.c

v veri :
	$(FC) $(FFLAGS) -mthread -print $T.c mthread_*.c > out.cc

poet :
	$(PPC) --merge --out=full.c --dopoet $T.c 
