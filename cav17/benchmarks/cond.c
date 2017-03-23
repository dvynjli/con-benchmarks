//#include "verifier-framac.h"
//#include "verifier-none.h"
//#include "verifier-poet.h"
#include "verifier-impara.h"
//#include "verifier-astreea.h"

#define NUM_THREADS 5
#define MIN 0
#define MAX 1000

pthread_mutex_t m; 

void* thr1(void* arg)
{
  int x;
  int y;
  int z;
  
  x = __VERIFIER_nondet_int(MIN, MAX);
  y = __VERIFIER_nondet_int(MIN, MAX);
  
  pthread_mutex_lock (&m);
  if(x == y)
  {
    z = 0;
  } else {
    z = 1;
  }

  printf ("thr1: x=%d, y=%d, z=%d\n", x,y,z);
  
  if(z == 0)
  {
    __VERIFIER_assert (x == y);
  } else {
    __VERIFIER_assert (x != y);
  }
  pthread_mutex_unlock (&m);
  
  return NULL;
}

int main()
{
   pthread_t t[NUM_THREADS];
   pthread_mutex_init (&m, NULL);

   // Unfolded loop
   int i = 0;
   pthread_create (&t[i], NULL, thr1, NULL); i++;
   pthread_create (&t[i], NULL, thr1, NULL); i++;
   pthread_create (&t[i], NULL, thr1, NULL); i++;
   pthread_create (&t[i], NULL, thr1, NULL); i++;
   pthread_create (&t[i], NULL, thr1, NULL); 

#if 0
   int i = 0;
   pthread_join (t[i], NULL); i++;
   pthread_join (t[i], NULL); i++;
   pthread_join (t[i], NULL); i++;
   pthread_join (t[i], NULL); i++;
   pthread_join (t[i], NULL); 
#endif

   return 0;
}

