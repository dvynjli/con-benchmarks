#include "verifier-impara.h"

#define MAX_QUEUE 4
#define MAX_ITEMS 6

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
   // int i = 0;
   printf ("prod: trying\n");
   while (done == 0)
   {
      // i++;
      pthread_mutex_lock (&mq);
      if (qsiz < MAX_QUEUE)
      {
         // printf ("prod: got it! x %d qsiz %d i %d\n", x, qsiz, i);
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
   //@ assert (mx >= 0);
   __VERIFIER_assert (mx >= 0);

   //@ assert (mx < count);
   __VERIFIER_assert (mx < count);

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

      //@ assert (idx >= 0);
      __VERIFIER_assert (idx >= 0);

      //@ assert (idx < MAX_ITEMS);
      __VERIFIER_assert (idx < MAX_ITEMS);

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
      //@ assert (idx >= 0);
      __VERIFIER_assert (idx >= 0);

      // global
      //@ assert (idx < MAX_ITEMS);
      __VERIFIER_assert (idx < MAX_ITEMS);

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
   int i;

   __libc_init_poet ();

   // initialize the source array
   for (i = 0; i < MAX_ITEMS; i++)
   {
      source[i] = __VERIFIER_nondet_int(0,20);
      printf ("m: init i %d source = %d\n", i, source[i]);
      //@ assert (source[i] >= 0);
      __VERIFIER_assert (source[i] >= 0);
   }

   // initialize shared variables
   queue_init ();

   // create one thread and run the consummer in the main thread
   pthread_create (&t, NULL, thread, NULL);
   consumer ();

   // join
   pthread_join (t, NULL);
   return 0;
}

