//#include "verifier-none.h"
#include "verifier-framac.h"
//#include "verifier-poet.h"
//#include "verifier-astrea.h"

#define NUM_THREADS 2
#define ELEM_PER_THREAD 20

#define SEQSIZE (NUM_THREADS * ELEM_PER_THREAD)

pthread_mutex_t mutexid; // = PTHREAD_MUTEX_INITIALIZER; <- frama-c does not support it
pthread_mutex_t mutexdone;
pthread_mutex_t mutexres;
int idcount = 0;
int donecount = 0;
int result[NUM_THREADS];
int target;
int sequence[SEQSIZE];

void *thread (void *arg)
{
	int id, i, from, count;

	// get an id
	pthread_mutex_lock (&mutexid);
	id = idcount;
	idcount++;
	pthread_mutex_unlock (&mutexid);
	__VERIFIER_assert (id >= 0);
	//@ assert (id >= 0);
	__VERIFIER_assert (id <= NUM_THREADS);
	//@ assert (id <= NUM_THREADS);

	// scan my part of the sequence and count the number of desired nucleotides
	from = id * ELEM_PER_THREAD;
	count = 0;
	for (i = 0; i < ELEM_PER_THREAD; i++)
	{
		if (sequence[from + i] == target) count++;
		if (count > ELEM_PER_THREAD) count = ELEM_PER_THREAD; // to recover precission ...
	}
	printf ("t: id %d from %d count %d\n", id, from, count);

	// send my result
	pthread_mutex_lock (&mutexres);
	result[id] = count;
	pthread_mutex_unlock (&mutexres);

#ifndef VERIFIER_HAVE_PTHREAD_JOIN
	pthread_mutex_lock (&mutexdone);
	donecount++;
	pthread_mutex_unlock (&mutexdone);
#endif
	return NULL;
}

int main ()
{
	int i;
	pthread_t t[NUM_THREADS];
	int count;

	// non-deterministically choose a DNA sequence
	// A = 0
	// T = 1
	// G = 2
	// C = 3
	for (i = 0; i < SEQSIZE; i++)
	{
		sequence[i] = __VERIFIER_nondet_int() % 4;
		printf ("m: init i %d seq %d\n", i, sequence[i]);
	}

	// non-deterministically choose a nucleotide to count
	target = __VERIFIER_nondet_int() % 4;

	// initialize shared variables
	pthread_mutex_init (&mutexid, NULL);
	pthread_mutex_init (&mutexdone, NULL);
	pthread_mutex_init (&mutexres, NULL);
	for (i = 0; i < NUM_THREADS; i++) result[i] = 0;

	// create the threads
	i = 0;
   pthread_create (&t[i++], NULL, thread, NULL);
   pthread_create (&t[i++], NULL, thread, NULL);
	__VERIFIER_assert (i == NUM_THREADS);
	//@ assert (i == NUM_THREADS);

	// wait for all threads to finish
#ifdef VERIFIER_HAVE_PTHREAD_JOIN
	i = 0;
   pthread_join (t[i++], NULL);
   pthread_join (t[i++], NULL);
	__VERIFIER_assert (i == NUM_THREADS);
	//@ assert (i == NUM_THREADS);
#else
	pthread_mutex_lock (&mutexdone);
	if (donecount != NUM_THREADS) return 0;
	pthread_mutex_unlock (&mutexdone);
#endif

	// merge the results
	count = 0;
	for (i = 0; i < NUM_THREADS; i++)
	{
		printf ("m: i %d result %d count %d\n", i, result[i], count);
		count += result[i];
	}

	printf ("m: final count %d\n", count);
	__VERIFIER_assert (count >= 0);
	//@ assert (count >= 0);
	__VERIFIER_assert (count <= SEQSIZE);
	//@ assert (count <= SEQSIZE);
	return 0;
}
