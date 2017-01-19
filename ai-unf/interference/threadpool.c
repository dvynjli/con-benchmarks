#include "verifier-framac.h"
//#include "verifier-none.h"
//#include "verifier-poet.h"
//#include "verifier-astrea.h"

pthread_mutex_t mut;
int control = 0; /* 0 / 1 / 2 == no request / request to work / work finished */
int arg;
int result;

pthread_mutex_t mutexdone;
int donecount = 0;

void spinlock_cas (int *var, pthread_mutex_t *mutex, int cmp, int set)
{
	// do a spinlock on variable "var", protected with "mutex" until the value
	// equals "cmp", then set to "set"
	
	int done = 0;
   while (! done)
	{
      pthread_mutex_lock (mutex);
      if (*var == cmp)
		{
			printf ("t: spinlock_cas: var %d cmp %d set %d\n", *var, cmp, set);
			done = 1;
			*var = set;
		}
      pthread_mutex_unlock (mutex);
   }
}

void spinlock_inc (int *var, pthread_mutex_t *mutex)
{
	// increment variable "var", protected with "mutex"

	pthread_mutex_lock (mutex);
	(*var)++;
	printf ("t: spinlock_inc: var %d\n", *var);
	pthread_mutex_unlock (mutex);
}

int last_bit_is_set (int a)
{
	return ((a / 2) * 2) != a;
}


int work (int arg_)
{
	// do some task, such as counting the number of ones in the binary
	// representation of arg_; we unroll the loop manually, so that all verifiers
	// achieve good precision

	int count = 0;

	printf ("t: work: arg_ %d\n", arg_);

	//@ assert (arg_ >= 0);
	__VERIFIER_assert (arg_ >= 0);
	//@ assert (arg_ < 1024);
	__VERIFIER_assert (arg_ < 1024);

	// fix here
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
	if (last_bit_is_set (arg_)) count++; if (! arg_) goto end; arg_ /= 2;
end:
	printf ("t: work: count %d\n", count);

	//@ assert (arg_ == 0);
	__VERIFIER_assert (arg_ == 0);
	//@ assert (count <= 10);
	__VERIFIER_assert (count <= 10);
	return count;
}

void *thread (void *arg_)
{
	while (1)
	{
		// wait for a request to work (control == 1)
		spinlock_cas (&control, &mut, 1, 1);

		// do the work using the provided arguments, or terminate
		if (arg == 1234) break;
		result = work (arg);

		// replay back to the main thread
		spinlock_inc (&control, &mut);
	}
	return NULL;
}

int main ()
{
   pthread_t t;
	int myres;

	// initialize shared variables and create the thread
   pthread_mutex_init (&mut, NULL);
   pthread_mutex_init (&mutexdone, NULL);
	donecount = 0;
	control = 0;
   pthread_create (&t, NULL, thread, NULL);

	printf ("m: thread created, control %d\n", control);

	// following read does not race
	//@ assert (control == 0);
	__VERIFIER_assert (control == 0);

   // =================================================
	// 1st request to work
	//arg = __VERIFIER_nondet_int (0, 1023);
	arg = 15;
   spinlock_inc (&control, &mut);
   spinlock_cas (&control, &mut, 2, 0);

	// check result
	myres = work (arg);
	printf ("m: result %d myres %d\n", result, myres);
	//@ assert (result == myres);
	__VERIFIER_assert (result == myres);
	//@ assert (control == 0);
	__VERIFIER_assert (control == 0);

   // =================================================
	// 2nd request to work
	//arg = __VERIFIER_nondet_int (0, 1023);
	arg = 254;
   spinlock_inc (&control, &mut);
   spinlock_cas (&control, &mut, 2, 0);

	// check result
	myres = work (arg);
	printf ("m: result %d myres %d\n", result, myres);
	//@ assert (result == myres);
	__VERIFIER_assert (result == myres);
	//@ assert (control == 0);
	__VERIFIER_assert (control == 0);
	
   // =================================================
	// final request to finish
	arg = 1234;
   spinlock_inc (&control, &mut);

	//@ assert (control == 1);
	__VERIFIER_assert (control == 1);

	// join
#ifdef VERIFIER_HAVE_PTHREAD_JOIN
   pthread_join (t, NULL);
#else
	pthread_mutex_lock (&mutexdone);
	if (donecount != 1) return 0;
	pthread_mutex_unlock (&mutexdone);
#endif
   return 0;
}
