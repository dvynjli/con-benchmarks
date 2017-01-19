//#include "verifier-framac.h"
#include "verifier-none.h"
//#include "verifier-poet.h"

#define NUM_ROBOTS 2

int source[NUM_ROBOTS];
// output channel for main
int out_channel[NUM_ROBOTS];
// input channel for main
int in_channel[NUM_ROBOTS];
int th_id = 0;

pthread_mutex_t mid;
pthread_mutex_t ms[NUM_ROBOTS];

void *robot (void * arg)
{
   // robot gets an id
   int id = -1;
   pthread_mutex_lock (&mid);
     id = th_id;
     th_id++;
   pthread_mutex_unlock (&mid);
   __VERIFIER_assert (id >= 0);
   
   // robot gets the square of his box
   int size = source[id];
   int dir = __VERIFIER_nondet_int() % 4;
   int position = __VERIFIER_nondet_int() % size;
   int duration = __VERIFIER_nondet_int() % 100;
   int battery = __VERIFIER_nondet_int() % 1000;
   
   do { 
     duration--;
     battery--;
  
     // compute the new position
     position = (position + 1) % size;
     
     // when the duration of the direction reaches 0
     // compute the next position 
     if (duration == 0)
     {
       dir = __VERIFIER_nondet_int() % 4;
       position = __VERIFIER_nondet_int() % size;
       duration = __VERIFIER_nondet_int() % 100;
     }

     if (battery == 0)
     { 
       pthread_mutex_lock (&ms[id]);
         // compute the new battery value 
         battery = __VERIFIER_nondet_int() % 1000;
         // get the value that main wrote 
         if (out_channel[id] > battery)
         {
           battery = out_channel[id];
           out_channel[id] = 0;
         } 
         // write to the input channel of main the new value for the battery 
         in_channel[id] = battery;
       pthread_mutex_unlock (&ms[id]);
     }
   } while (battery >= 0);

   return NULL;
}

int main ()
{
   pthread_t ths[NUM_ROBOTS];

   pthread_mutex_init (&mid, NULL);
   __libc_init_poet ();

   // this code initializes the source array with random numbers
   unsigned seed = (unsigned) time(0);
   srand (seed);
   printf ("Using seed %u\n", seed);
   int i;
   for (i = 0; i < NUM_ROBOTS; i++)
   {
      source[i] = __VERIFIER_nondet_int() % 20;
      printf ("source[%d] = %d\n", i, source[i]);
      __VERIFIER_assert (source[i] >= 0);
   }
   printf ("==============\n");

   // this code initializes the mutexes, the channel and the minBound and maxBounds
   for (i = 0; i < NUM_ROBOTS; i++)
   {
     out_channel[i] = __VERIFIER_nondet_int() % 1000;
     pthread_mutex_init (&ms[i], NULL);
     pthread_create (&ths[i], NULL, robot, NULL);
   }


   int k = 0;
   int t = 0;
   int aux = 0;

   while (k <= NUM_ROBOTS)
   {
     // sample a random thread
     tid = __VERIFIER_nondet_int() % NUM_ROBOTS;

     pthread_mutex_lock (&ms[tid]);
       aux = in_channel[id];
       if (aux == 0)
       {
         k++;
       }
     pthread_mutex_unlock (&ms[tid]);

     for (int a = aux; a >= 0; a--)
     {
       aux--;
     }

     pthread_mutex_lock (&ms[tid]);
       out_channel[tid] = __VERIFIER_nondet_int() % 1000;
     pthread_mutex_unlock (&ms[tid]);
   }

   // if the tool supports join
#if 1
   for (i = 0; i < NUM_ROBOTS; i++) 
   { 
     pthread_join (ths[i], NULL);
   }
#endif

   return 0;
}

