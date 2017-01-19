
#ifndef _VERIFIER__
#define _VERIFIER__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define VERIFIER_NONE

static void __VERIFIER_error()
{
	printf ("__VERIFIER_error\n");
   abort ();
}

static int  __VERIFIER_nondet_int()
{
   return rand ();
}

static void __VERIFIER_assume(int expr)
{
   if (! (expr))
		printf ("__VERIFIER_assume (%d) executed!!!!\n", expr);
}

void __VERIFIER_assert (int expr)
{
   if (! (expr))
	{
		printf ("__VERIFIER_assert (%d) executed!!!!\n", expr);
	}
}

#ifdef assert
#undef assert
#endif

#define assert __VERIFIER_assert

#ifdef __KLIBC__
	#include <klibc/poet.h>
#else
	#define __libc_init_poet()
#endif

#endif
