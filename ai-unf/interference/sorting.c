//#include "verifier-framac.h"
//#include "verifier-none.h"
#include "verifier-poet.h"
//#include "verifier-astreea.h"

#define NUM_THREADS 2
#define MAX_ITEMS 7

int source[MAX_ITEMS];
int minBound[NUM_THREADS];
int maxBound[NUM_THREADS];
int channel[NUM_THREADS];
int th_id = 0;

pthread_mutex_t mid;
pthread_mutex_t ms[NUM_THREADS];

void sort (int x, int y)
{
  int aux = 0;
  for (int i = x; i < y; i++) // I think this is buggy ...
  {
    for (int j = i; j < y; j++)
    {
      if (source[i] > source[j])
      {
        aux = source[i];
        source[i] = source[j];
        source[j] = aux;
      }
    }
  }
}

void *sort_thread (void * arg)
{
   int id = -1;
   int x, y;

   // get an id
   pthread_mutex_lock (&mid);
   id = th_id;
   th_id++;
   pthread_mutex_unlock (&mid);

   // get my indexes
   x = minBound[id];
   y = maxBound[id];
   
   // check bounds
   //@ assert (x >= 0);
   __VERIFIER_assert (x >= 0);
   //@ assert (x < MAX_ITEMS);
   __VERIFIER_assert (x < MAX_ITEMS);
   //@ assert (y >= 0);
   __VERIFIER_assert (y >= 0);
   //@ assert (y < MAX_ITEMS);
   __VERIFIER_assert (y < MAX_ITEMS);
   
   // sort
   printf ("t%d: min %d max %d\n", id, x, y);
   sort (x, y);
   
   // I'm done
   pthread_mutex_lock (&ms[id]);
   channel[id] = 1;
   pthread_mutex_unlock (&ms[id]);
   return NULL;
}

int main ()
{
   pthread_t t[NUM_THREADS];
   int i;

   __libc_init_poet ();

   // this code initializes the source array with random numbers
   i = __VERIFIER_nondet_int (0, MAX_ITEMS - 1);
   source[i] = __VERIFIER_nondet_int (0, 20);

   //@ assert (source[i] >= 0);
   __VERIFIER_assert (source[i] >= 0);

   // init shared variables
   pthread_mutex_init (&mid, NULL);

   // this code initializes the mutexes, the channel and the minBound and maxBounds
   int j = 0;
   int delta = MAX_ITEMS/NUM_THREADS;

   //@ assert (delta >= 1);
   __VERIFIER_assert (delta >= 1);

   // start threads (unfolded loop)
   i = 0;
#define ITER \
   channel[i] = 0; \
   minBound[i] = j; \
   maxBound[i] = j + delta -1; \
   j += delta; \
   pthread_mutex_init (&ms[i], NULL); \
   pthread_create (&t[i], NULL, sort_thread, NULL); \
   i++;
   ITER
   ITER
#undef ITER
   //@ assert (i == NUM_THREADS);
   __VERIFIER_assert (i == NUM_THREADS);

   // wait for all the threads to finish the sorting
   int k = 0;
   while (k < NUM_THREADS)
   {
     // check if any thread finished (unfolded loop)
     // THIS LOOP CONTAINS A BUG
     // The loop should terminate only after ALL thread have finished, but it
     // can terminate after only ONE thread terminates, as it can increase k
     // multiple times using the channel bit of that thread. As a result the
     // assertions below can be violated
     i = 0;
#define ITER \
     pthread_mutex_lock (&ms[i]); \
     if (channel[i] == 1) { k++; } \
     pthread_mutex_unlock (&ms[i]); \
     i++;
     ITER
     ITER
#undef ITER
     //@ assert (i == NUM_THREADS);
     __VERIFIER_assert (i == NUM_THREADS);
   }

   // check that the correct number of threads was created
   //@ assert (th_id == NUM_THREADS);
   __VERIFIER_assert (th_id == NUM_THREADS);

   // check that the correct number of threads has terminated 
   //@ assert (k == NUM_THREADS);
   __VERIFIER_assert (k == NUM_THREADS);

   // merge the sorted arrays (we should merge here, instead of sorting again!!)
   sort (0, MAX_ITEMS);
 
   // print the sorted array
   printf ("==============\n");
   for (i = 0; i < MAX_ITEMS; i++)
      printf ("m: sorted[%d] = %d\n", i, source[i]);

   // join (all threads must have exited by now, due to the loop above, so if
   // the verifier does not support join, that won't impact the precission)
   i = 0;
   pthread_join (t[i], NULL); i++;
   pthread_join (t[i], NULL); i++;
   //@ assert (i == NUM_THREADS);
   __VERIFIER_assert (i == NUM_THREADS);

   return 0;
}
