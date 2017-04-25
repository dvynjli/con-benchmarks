#ifndef _VERIFIER__
#define _VERIFIER__

#include <pthread.h>
#include <assert.h>

#define VERIFIER_IMPARA
#define VERIFIER_HAVE_PTHREAD_JOIN

int nondet();

void __VERIFIER_error();

#define __VERIFIER_nondet_int __IMPARA_nondet_int

int  __IMPARA_nondet_int(int min, int max)
{
  int x = nondet();
  __CPROVER_assume (x >= min);
  __CPROVER_assume (x <= max);
  return x; 
}

void __VERIFIER_assume(int expr);

void __VERIFIER_assert (expr)
{
   assert (expr);
}

#endif
