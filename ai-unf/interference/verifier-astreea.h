
#ifndef _VERIFIER__
#define _VERIFIER__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define VERIFIER_ASTREEA
#undef VERIFIER_HAVE_PTHREAD_JOIN

void __VERIFIER_error()
{
   abort ();
}

int  __VERIFIER_nondet_int(int min, int max)
{
	max++;
   return min + (rand() % max);
}

void __VERIFIER_assume(int expr)
{
   // not used :)
}

#define __VERIFIER_assert(expr) assert (expr)

#define __libc_init_poet()

#endif
