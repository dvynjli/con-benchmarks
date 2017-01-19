//#include "verifier-framac.h"
//#include "verifier-none.h"
#include "verifier-poet.h"
//#include "verifier-astrea.h"

#define MAX_QUEUE 2
#define MAX_ITEMS 3

int q[MAX_QUEUE];
int qsiz;
pthread_mutex_t mq;
pthread_mutex_t mutexdone;
int donecount = 0;

void queue_init ()
{
   pthread_mutex_init (&mq, NULL);
   qsiz = 0;
}

void queue_insert (int x)
{
   int done = 0;
  // int i = 0;
   printf ("prod: trying\n");
   while (done == 0)
   {
    //  i++;
      pthread_mutex_lock (&mq);
      if (qsiz < MAX_QUEUE)
      {
      //   printf ("prod: got it! x %d qsiz %d i %d\n", x, qsiz, i);
         done = 1;
         q[qsiz] = x;
         qsiz++;
      }
      pthread_mutex_unlock (&mq);
   }
}

int queue_extract ()
{
   int done = 0;
   int x = -1, i = 0;
   printf ("consumer: trying\n");
   while (done == 0)
   {
   //   i++;
      pthread_mutex_lock (&mq);
      if (qsiz > 0)
      {
         done = 1;
         x = q[0];
   //      printf ("consumer: got it! x %d qsiz %d i %d\n", x, qsiz, i);
         qsiz--;
         for (i = 0; i < qsiz; i++) q[i] = q[i+1]; // shift left 1 elem
         __VERIFIER_assert (qsiz < MAX_QUEUE);
         q[qsiz] = 0;
      }
      pthread_mutex_unlock (&mq);
   }
   return x;
}

void swap (int *t, int i, int j)
{
   int aux;
   aux = t[i];
   t[i] = t[j];
   t[j] = aux;
}

int findmaxidx (int *t, int count)
{
   int i, mx;
   mx = 0;
   for (i = 1; i < count; i++)
   {
      if (t[i] > t[mx]) mx = i;
   }
	// local
   __VERIFIER_assert (mx >= 0);
   //@ assert (mx >= 0);

	// local
   __VERIFIER_assert (mx < count);
   //@ assert (mx < count);

   t[mx] = -t[mx];
   return mx;
}

int source[MAX_ITEMS];
int sorted[MAX_ITEMS];

void producer ()
{
   int i, idx;

   for (i = 0; i < MAX_ITEMS; i++)
   {
      idx = findmaxidx (source, MAX_ITEMS);

		// local
      __VERIFIER_assert (idx >= 0);
      //@ assert (idx >= 0);

		// local
      __VERIFIER_assert (idx < MAX_ITEMS);
      //@ assert (idx < MAX_ITEMS);

      queue_insert (idx);
   }
}

void consumer ()
{
   int i, idx;
   for (i = 0; i < MAX_ITEMS; i++)
   {
      idx = queue_extract ();
      sorted[i] = idx;
      printf ("m: i %d sorted = %d\n", i, sorted[i]);

		// global
      __VERIFIER_assert (idx >= 0);
      //@ assert (idx >= 0);

		// global
      __VERIFIER_assert (idx < MAX_ITEMS);
      //@ assert (idx < MAX_ITEMS);

		// global, requires relational domain, does not race; wont be able to
		// prove it with poet, frama-c or AstreA
      __VERIFIER_assert (source[idx] < 0);
      ////@ assert (source[idx] < 0);
   }
}

void *thread (void * arg)
{
   (void) arg;
   producer ();

#ifndef VERIFIER_HAVE_PTHREAD_JOIN
	pthread_mutex_lock (&mutexdone);
	donecount++;
	pthread_mutex_unlock (&mutexdone);
#endif
   return NULL;
}

int main ()
{
   pthread_t t;
   int i;

   __libc_init_poet ();

	// initialize the source array
   for (i = 0; i < MAX_ITEMS; i++)
   {
      source[i] = __VERIFIER_nondet_int(0,20);
      printf ("m: init i %d source = %d\n", i, source[i]);
		__VERIFIER_assert (source[i] >= 0);
		//@ assert (source[i] >= 0);
   }

	// initialize shared variables
   queue_init ();
   pthread_mutex_init (&mutexdone, NULL);

	// create one thread and run the consumer in the main thread
   pthread_create (&t, NULL, thread, NULL);
   consumer ();

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

