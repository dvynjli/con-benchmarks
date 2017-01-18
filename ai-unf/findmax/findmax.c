//#include "verifier-framac.h"
#include "verifier-none.h"
//#include "verifier-poet.h"
//#include "verifier-astrea.h"

#define MAX_QUEUE 5
#define MAX_ITEMS 7

int q[MAX_QUEUE];
int qsiz;
pthread_mutex_t mq;

void queue_init ()
{
   pthread_mutex_init (&mq, NULL);
   qsiz = 0;
}

void queue_insert (int x)
{
   int done = 0;
   int i = 0;
   printf ("prod: trying\n");
   while (done == 0)
   {
      i++;
      pthread_mutex_lock (&mq);
      if (qsiz < MAX_QUEUE)
      {
         printf ("prod: got it! x %d qsiz %d i %d\n", x, qsiz, i);
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
      i++;
      pthread_mutex_lock (&mq);
      if (qsiz > 0)
      {
         done = 1;
         x = q[0];
         printf ("consumer: got it! x %d qsiz %d i %d\n", x, qsiz, i);
         qsiz--;
         for (i = 0; i < qsiz; i++) q[i] = q[i+1]; // shift left 1 elem
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
		printf ("idx %d\n", idx);
		printf ("MAX_ITEMS %d\n", MAX_ITEMS);
		printf ("source[idx] %d\n", source[idx]);

		// global
      __VERIFIER_assert (idx >= 0);
      //@ assert (idx >= 0);

		// global
      __VERIFIER_assert (idx < MAX_ITEMS);
      //@ assert (idx < MAX_ITEMS);

		// global, requires relational domain, does not race; wont be able to
		// prove it with poet, frama-c or AstreA
      //__VERIFIER_assert (source[idx] < 0);
      ////@ assert (source[idx] < 0);
   }
}

void *thread (void * arg)
{
   (void) arg;
   producer ();
   return NULL;
}

int main ()
{
   pthread_t t;

   __libc_init_poet ();

   // this code initializes the source array with random numbers
   //unsigned seed = (unsigned) 123; // time(0);
   //srand (seed);
   //printf ("Using seed %u\n", seed);
   int i;
   for (i = 0; i < MAX_ITEMS; i++)
   {
      source[i] = __VERIFIER_nondet_int() % 20;
      printf ("source[%d] = %d\n", i, source[i]);
		__VERIFIER_assert (source[i] >= 0);
   }
   printf ("==============\n");
	__VERIFIER_assert (source[3] >= 0);

   queue_init ();
   pthread_create (&t, NULL, thread, NULL);
   consumer ();
   pthread_join (t, NULL);

#if 1
   // this code prints the sorted array
   printf ("==============\n");
   for (i = 0; i < MAX_ITEMS; i++)
      printf ("sorted[%d] = %d\n", i, sorted[i]);
#endif
   return 0;
}

