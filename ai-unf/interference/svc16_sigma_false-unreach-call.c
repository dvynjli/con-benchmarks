//#include "verifier-framac.h"
//#include "verifier-none.h"
#include "verifier-poet.h"
//#include "verifier-astreea.h"

#define SIGMA 4

int array[SIGMA];
int array_index = 0;

pthread_mutex_t  mutex;

void *thread(void * arg)
{
   pthread_mutex_lock(&mutex);
     array[array_index] = 1;
   pthread_mutex_unlock(&mutex);

   return 0;
}

int main()
{
   int i, sum;
   pthread_t t[SIGMA];
   pthread_mutex_init(&mutex, 0);

   // create the threads (unfolded loop)
   i = 0;
   pthread_create(&t[i], 0, thread, 0);
   pthread_mutex_lock(&mutex); array_index++; pthread_mutex_unlock(&mutex); i++;
   pthread_create(&t[i], 0, thread, 0); 
   pthread_mutex_lock(&mutex); array_index++; pthread_mutex_unlock(&mutex); i++;
   pthread_create(&t[i], 0, thread, 0); 
   pthread_mutex_lock(&mutex); array_index++; pthread_mutex_unlock(&mutex); i++;
   pthread_create(&t[i], 0, thread, 0); 
   pthread_mutex_lock(&mutex); array_index++; pthread_mutex_unlock(&mutex); i++;

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

   sum = 0;
   i = 0;
   sum += array[i];  i++;
   sum += array[i];  i++;
   sum += array[i];  i++;
   sum += array[i];  i++;

   printf ("m: sum %d SIGMA %d\n", sum, SIGMA);
   //@ assert (sum <= SIGMA);
   __VERIFIER_assert (sum <= SIGMA);

   return 0;
}
