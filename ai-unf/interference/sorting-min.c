// THIS PROGRAM IS GETTING TOO COMPLEX
// WILL FINISH IT IF NECESSARY
//#include "verifier-framac.h"
#include "verifier-none.h"
//#include "verifier-poet.h"

#define NUM_THREADS 2
#define MAX_ITEMS 7

int source[MAX_ITEMS];
int minBound[NUM_THREADS];
int maxBound[NUM_THREADS];
int channel[NUM_THREADS];
int th_id = 0;

pthread_mutex_t mid;
pthread_mutex_t ms[NUM_THREADS];

int findmin (int x, int y)
{
  int idx = -1;
  int val = source[x];
  for (int i = x+1; i < y; i++)
  {
    if (val > source[i])
    {
      idx = i;
      val = source[i];
    }
  }

  __VERIFIER_assert (idx >= x);
  __VERIFIER_assert (idx < y);
  return idx;
}

int findmin_channel ()
{
  int idx = 0;
  int val = channel[idx];

  for (int i = 1; i < NUM_THREADS; i++)
  {
    if (val > channel[i])
    {
      idx = i;
      val = source[i];
    }
  }

  __VERIFIER_assert (idx >= 0);
  __VERIFIER_assert (idx < NUM_THREADS);
  return idx;
}

void *sort_thread (void * arg)
{
   int id = -1;
   pthread_mutex_lock (&mid);
     id = th_id;
     th_id++;
   pthread_mutex_unlock (&mid);
   
   __VERIFIER_assert (id >= 0);
   
   int min, max = -1;
   // get the first min and max bound
   pthread_mutex_lock (&ms[id]);
     min = minBound[id];
     max = maxBound[id];
   pthread_mutex_unlock (&ms[id]);

   __VERIFIER_assert (min >= 0);
   __VERIFIER_assert (min <= max);

   // 
   int val = findmin (min, max);
   int _val = 0;

   while (min < max)
   {
     pthread_mutex_lock (&ms[id]);
       _val = channel[id];
       
     pthread_mutex_unlock (&ms[id]);
   }

   return NULL;
}

int main ()
{
   pthread_t ths[NUM_THREADS];

   pthread_mutex_init (&mid, NULL);
   __libc_init_poet ();

   // this code initializes the source array with random numbers
   unsigned seed = (unsigned) time(0);
   srand (seed);
   printf ("Using seed %u\n", seed);
   int i;
   for (i = 0; i < MAX_ITEMS; i++)
   {
      source[i] = __VERIFIER_nondet_int() % 20;
      printf ("source[%d] = %d\n", i, source[i]);
      __VERIFIER_assert (source[i] >= 0);
   }
   printf ("==============\n");

   // this code initializes the mutexes, the channel and the minBound and maxBounds
   int j = 0;
   int delta = MAX_ITEMS/NUM_THREADS;
   for (i = 0; i < NUM_THREADS; i++)
   {
     channel[i] = 0;
     minBound[i] = j;
     maxBound[i] = j+delta; 
     j+=delta+1;
     pthread_mutex_init (&ms[i], NULL);
     pthread_create (&ths[i], NULL, sort_thread, NULL);
   }

#if 1
   for (i = 0; i < MAX_ITEMS; i++)
   {
     // get the minimal elements of each sub-array 
     for (j = 0; j < NUM_THREADS; j++)
     {
              
     }  
   }
#endif

   // if the tool supports join
#if 1
   for (i = 0; i < NUM_THREADS; i++) 
   { 
     pthread_join (ths[i], NULL);
   }
#endif

   // now that all the threads are done
   // main will join the results
   // this method should be optimized
   // but it is just simulating computation
   sort (0, MAX_ITEMS);
 
#if 1
   // this code prints the sorted array
   printf ("==============\n");
   for (i = 0; i < MAX_ITEMS; i++)
      printf ("sorted[%d] = %d\n", i, sorted[i]);
#endif
   return 0;
}

