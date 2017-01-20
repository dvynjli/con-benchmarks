//#include "verifier-framac.h"
//#include "verifier-none.h"
//#include "verifier-poet.h"
#include "verifier-astreea.h"

#define NUM_ROBOTS 2

#define MAX_RECHARGE 10
#define MAX_DURATION 50
#define MAX_BOARD_SIZE 20

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
   //@ assert (id >= 0);
   __VERIFIER_assert (id >= 0);
   //@ assert (id < NUM_ROBOTS);
   __VERIFIER_assert (id < NUM_ROBOTS);
   
   // robot gets the (1-dimensional) area of work, we start at position 0 with
   // no duration and no battery
   int size = source[id];
   int dir = 0;
   int position = 0;
   int duration = 0;
   int battery = 0;
   
   // we walk for "duration" seconds
   while (1)
   {
     printf ("t: id %d dir %d pos %d dur %d bat %d\n", id, dir, position, duration, battery);

     // if we run out of battery, ask for more power to the main thread
     if (battery == 0)
     {
       pthread_mutex_lock (&ms[id]);
       battery = out_channel[id];
       pthread_mutex_unlock (&ms[id]);
       if (battery == 0) break;
     }

     // choose a direction and a duration when we expire the duration time
     if (duration == 0)
     {
       duration = __VERIFIER_nondet_int(1, MAX_DURATION);
       dir = __VERIFIER_nondet_int (0, 1);
       if (dir == 0) dir = -1;
     }

     // compute the new position
     duration--;
     battery--;
     position += dir;
     if (position >= size) position = 0;
     if (position < 0) position = size - 1;
   }

   return NULL;
}

int main ()
{
   int i, k, tid;
   pthread_t ths[NUM_ROBOTS];

   __libc_init_poet ();

   // this code initializes the source array with random numbers
   for (i = 0; i < NUM_ROBOTS; i++)
   {
      source[i] = __VERIFIER_nondet_int (0, MAX_BOARD_SIZE);
      printf ("m: source[%d] = %d\n", i, source[i]);
      //@ assert (source[i] >= 0);
      __VERIFIER_assert (source[i] >= 0);
   }
   printf ("==============\n");

   // initialize the mutexes, the channels, and create the threads (loop
   // unfolded)
   pthread_mutex_init (&mid, NULL);
   i = 0;
   out_channel[i] = MAX_RECHARGE;
   pthread_mutex_init (&ms[i], NULL);
   pthread_create (&ths[i], NULL, robot, NULL);
   i++;
   out_channel[i] = MAX_RECHARGE;
   pthread_mutex_init (&ms[i], NULL);
   pthread_create (&ths[i], NULL, robot, NULL);
   i++;
   //@ assert (i == NUM_ROBOTS);
   __VERIFIER_assert (i == NUM_ROBOTS);

   // we non-deterministically recharge or stop a robot, until all of them have
   // stopped
   k = 0;
   while (k < NUM_ROBOTS)
   {
     // choose a random robot that still works
     tid = __VERIFIER_nondet_int (0, NUM_ROBOTS - 1);
     if (out_channel[tid] == 0) continue;
     printf ("m: picking tid %d out[tid] %d\n", tid, out_channel[tid]);

     // recharge the battery or stop it
     pthread_mutex_lock (&ms[tid]);
     out_channel[tid] = __VERIFIER_nondet_int (0, MAX_RECHARGE);
     printf ("m: charging tid %d out[tid] %d\n", tid, out_channel[tid]);
     if (out_channel[tid] == 0)
     {
       k++;
     }
     pthread_mutex_unlock (&ms[tid]);
   }

   // join (loop unfolded)
   i = 0;
   pthread_join (ths[i], NULL); i++;
   pthread_join (ths[i], NULL); i++;
   //@ assert (i == NUM_ROBOTS);
   __VERIFIER_assert (i == NUM_ROBOTS);
   return 0;
}

