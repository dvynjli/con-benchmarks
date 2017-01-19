#ifndef _VERIFIER__
#define _VERIFIER__

#include "poet_pthread.h"

#define VERIFIER_POET
#undef VERIFIER_HAVE_PTHREAD_JOIN

void __VERIFIER_error();
int  __VERIFIER_nondet_int(int, int);
void __VERIFIER_assume(int expr);

#define __VERIFIER_assert(expr) \
   if (! (expr)) { \
      __VERIFIER_error (); \
   }

#define assert __VERIFIER_assert

#ifdef __KLIBC__
	#include <klibc/poet.h>
#else
	#define __libc_init_poet()
#endif // __KLIBC__

#define printf(fmt,args...)
#define NULL ((void*) 0)

#endif
