//#include "verifier-framac.h"
//#include "verifier-none.h"
//#include "verifier-poet.h"
#include "verifier-astreea.h"

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
   pthread_create(&t[i], 0, thread, 0); array_index++; i++;
   //@ assert (i == SIGMA);
   __VERIFIER_assert (i == SIGMA);

   // join
   i = 0;
   pthread_join (t[i], 0); i++;
   pthread_join (t[i], 0); i++;
   pthread_join (t[i], 0); i++;
   pthread_join (t[i], 0); i++;
   //@ assert (i == SIGMA);
   __VERIFIER_assert (i == SIGMA);

   for (i = sum = 0; i < SIGMA; i++) {
      sum += array[i];
   }

   printf ("m: sum %d SIGMA %d\n", sum, SIGMA);
   //@ assert (sum == SIGMA);
   __VERIFIER_assert (sum == SIGMA);

   return 0;
}
