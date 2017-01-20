//#include "verifier-framac.h"
//#include "verifier-none.h"
#include "verifier-poet.h"
//#include "verifier-astreea.h"

#define SIGMA 4

int array[SIGMA];
int array_index = 0;

void *thread(void * arg)
{
   array[array_index] = 1;

   return 0;
}

int main()
{
   int i, sum;
   pthread_t t[SIGMA];

   // create the threads (unfolded loop)
   i = 0;
   pthread_create(&t[i], 0, thread, 0); array_index++; i++;
   pthread_create(&t[i], 0, thread, 0); array_index++; i++;
   pthread_create(&t[i], 0, thread, 0); array_index++; i++;
   pthread_create(&t[i], 0, thread, 0); i++; // last time don't increment array_index
   //@ assert (i == SIGMA);
   __VERIFIER_assert (i == SIGMA);
   //@ assert (array_index < SIGMA);
   __VERIFIER_assert (array_index < SIGMA);

   // join (on this benchmark, unlike the others, there is no good way to do a
   // join using only critical sections because here we don't need to distribute
   // ids to the threads)
   i = 0;
   pthread_join (t[i], 0); i++;
   pthread_join (t[i], 0); i++;
   pthread_join (t[i], 0); i++;
   pthread_join (t[i], 0); i++;
   //@ assert (i == SIGMA);
   __VERIFIER_assert (i == SIGMA);

   // aggregate results
   sum = 0;
   for (i = 0; i < SIGMA; i++) {
      sum += array[i];
   }

   printf ("m: sum %d SIGMA %d\n", sum, SIGMA);
   //@ assert (sum == SIGMA);
   __VERIFIER_assert (sum == SIGMA);

   return 0;
}
