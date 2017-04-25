#include "verifier-impara.h"

#define NUM_THREADS 3
#define ELEM_PER_THREAD 30

#define SEQSIZE (NUM_THREADS * ELEM_PER_THREAD)

pthread_mutex_t mutexid; // = PTHREAD_MUTEX_INITIALIZER; <- frama-c does not support it
pthread_mutex_t mutexres;
int idcount = 0;
pthread_mutex_t joinmutex[NUM_THREADS];
int join[NUM_THREADS];
int result[NUM_THREADS];
int target;
int sequence[SEQSIZE];

void *thread (void *arg)
{
   int id, i, from, count, l_target;
   // get an id
   pthread_mutex_lock (&mutexid);
   l_target = target;
   id = idcount;
   idcount++;
   pthread_mutex_unlock (&mutexid);
   //@ assert (id >= 0);
   __VERIFIER_assert (id >= 0);

   //@ assert (id <= NUM_THREADS);
   __VERIFIER_assert (id <= NUM_THREADS);

   // scan my part of the sequence and count the number of desired nucleotides
   from = id * ELEM_PER_THREAD;
   count = 0;

   for (i = 0; i < ELEM_PER_THREAD; i++)
   {
      if (sequence[from + i] == l_target)
      {
        count++;
      }
      if (count > ELEM_PER_THREAD)
      { 
        count = ELEM_PER_THREAD; // to recover precission ...
      }
   }
   printf ("t: id %d from %d count %d\n", id, from, count);

   // send my result
   pthread_mutex_lock (&mutexres);
   result[id] = count;
   pthread_mutex_unlock (&mutexres);

   // signal my join
#ifndef VERIFIER_HAVE_PTHREAD_JOIN
   pthread_mutex_lock (&joinmutex[id]);
   join[id] = 1;
   pthread_mutex_unlock (&joinmutex[id]);
#endif
   return NULL;
}

int main ()
{
   int i;
   pthread_t t[NUM_THREADS];
   int count;

   // __libc_init_poet ();

   // non-deterministically choose a DNA sequence
   // A = 0
   // T = 1
   // G = 2
   // C = 3
   i = __VERIFIER_nondet_int (0, SEQSIZE-1);
   sequence[i] = __VERIFIER_nondet_int (0, 3);

   // non-deterministically choose a nucleotide to count
   target = __VERIFIER_nondet_int (0, 3);
   printf ("m: target %d\n", target);

   // initialize shared variables
   pthread_mutex_init (&mutexid, NULL);
   pthread_mutex_init (&mutexres, NULL);
   for (i = 0; i < NUM_THREADS; i++)
   {
     pthread_mutex_init (&joinmutex[i], NULL);
     result[i] = 0;
     join[i] = 0;
   }

   // create the threads
   i = 0;
   pthread_create (&t[i], NULL, thread, NULL); i++;
   pthread_create (&t[i], NULL, thread, NULL); i++;
   pthread_create (&t[i], NULL, thread, NULL); i++;
   //@ assert (i == NUM_THREADS);
   __VERIFIER_assert (i == NUM_THREADS);

   // wait for all threads to finish
#ifdef VERIFIER_HAVE_PTHREAD_JOIN
   i = 0;
   pthread_join (t[i], NULL); i++;
   pthread_join (t[i], NULL); i++;
   pthread_join (t[i], NULL); i++;
   //@ assert (i == NUM_THREADS);
   __VERIFIER_assert (i == NUM_THREADS);
#else
   int j;
   i = 0;
#define ITER \
   pthread_mutex_lock (&joinmutex[i]); \
   j = join[i]; \
   pthread_mutex_unlock (&joinmutex[i]); \
   i++; \
   if (j == 0) \
   { \
     return 0; \
   }
   ITER
   ITER
   ITER
   if (i != NUM_THREADS)
   { 
     return 0;
   }
#undef ITER
   //@ assert (i == NUM_THREADS);
   __VERIFIER_assert (i == NUM_THREADS);
#endif

   // aggregate results
   count = 0;
   for (i = 0; i < NUM_THREADS; i++)
   {
      count += result[i];
      printf ("m: i %d result %d count %d\n", i, result[i], count);
   }

   printf ("m: final count %d\n", count);
   //@ assert (count >= 0);
   __VERIFIER_assert (count >= 0);

   //@ assert (count <= SEQSIZE);
   __VERIFIER_assert (count <= SEQSIZE);
   return 0;
}
