#ifndef _VERIFIER__
#define _VERIFIER__

#include <stdint.h>
#include <stdlib.h>
//#include <malloc.h>

#include "__fc_builtin.h"
#include <mthread_pthread.h>

#define VERIFIER_FRAMAC
#undef VERIFIER_HAVE_PTHREAD_JOIN

static void __VERIFIER_error()
{
  Frama_C_show_each ("__VERIFIER_error called");
  Frama_C_abort ();
}

static int  __VERIFIER_nondet_int()
{
   return rand ();
}

static void __VERIFIER_assume(int expr)
{
   (void) expr;
}

#define __VERIFIER_assert(expr) \
   if (! (expr)) { \
		/*@ ! assert expr; */ \
      Frama_C_show_each_warning ("assertion failed: " #expr " is ", expr); \
      __VERIFIER_error (); \
   }

#define assert __VERIFIER_assert

#ifdef __KLIBC__
	#include <klibc/poet.h>
#else
	#define __libc_init_poet()
#endif // __KLIBC__

// redefine printf and friends
#define printf			Frama_C_show_each
#define fprintf		Frama_C_show_each
#define sprintf		Frama_C_show_each
#define snprintf		Frama_C_show_each
#define asprintf		Frama_C_show_each
#define vasprintf		Frama_C_show_each

#endif
