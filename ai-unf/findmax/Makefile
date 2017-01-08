
include ~/x/devel/poet/libc/inc.mk

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

all : main
	./main

clean :
	rm -f main *.o full.c
