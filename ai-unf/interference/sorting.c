//#include "verifier-framac.h"
#include "verifier-none.h"
//#include "verifier-poet.h"
//#include "verifier-astrea.h"

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
  for (int i = x; i < y; i++)
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
   pthread_mutex_lock (&mid);
     id = th_id;
     th_id++;
   pthread_mutex_unlock (&mid);
   
   __VERIFIER_assert (id >= 0);
   
   sort (minBound[id], maxBound[id]);
   
   pthread_mutex_lock (&ms[id]);
     channel[id] = 1;
   pthread_mutex_unlock (&ms[id]);

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
      source[i] = __VERIFIER_nondet_int (0, 20);
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

   // wait for all the threads to finish the sorting
#if 1
   int k = 0;
   i = 0;
   do 
   {
     pthread_mutex_lock (&ms[i]);
       if (channel[i] != 0)
       {
         k++;
       }
     pthread_mutex_unlock (&ms[i]);
     i++; 
     if (i == NUM_THREADS)
     {
       i = 0;
     }
   } while (k < NUM_THREADS);

   // check that the correct number of threads was created
   __VERIFIER_assert (th_id == NUM_THREADS);
   // check the bounds
   __VERIFIER_assert (i >= 0);
   __VERIFIER_assert (i < NUM_THREADS);
   // check that the correct number of threads has terminated 
   __VERIFIER_assert (k == NUM_THREADS);
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
      printf ("sorted[%d] = %d\n", i, source[i]);
#endif
   return 0;
}

