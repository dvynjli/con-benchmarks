
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
CPPFLAGS=
CFLAGS=-Wall -pthread
CC=clang
LDLIBS=


FCROOT=~/x/devel/frama-c-Aluminium-20160501+dev
FC=$(FCROOT)/bin/frama-c
FFLAGS=-machdep x86_64 -no-unicode -slevel 1 -wlevel 10 -mt-verbose 2

all : main
	./main

clean :
	rm -f main *.o full.c

v veri :
	$(FC) $(FFLAGS) -mthread -print main-framac.c mthread_*.c > out.cc
