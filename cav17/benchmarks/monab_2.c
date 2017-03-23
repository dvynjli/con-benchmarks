//#include "verifier-framac.h"
//#include "verifier-none.h"
//#include "verifier-poet.h"
#include "verifier-impara.h"
//#include "verifier-astreea.h"

#define NUM_THREADS 5
#define MIN 0
#define MAX 1000

pthread_mutex_t m; 

int s = 0;
int l = 0;

void* thr1(void* arg)
{
  pthread_mutex_lock (&m);
  __VERIFIER_assert (l==0 || s==1);
  s = 1; // changed from s = s || 1
  l = 1; // overapproximates
  pthread_mutex_unlock (&m);

  return NULL;
}

int main()
{
  // added this initialization
  s = __VERIFIER_nondet_int(MIN, MAX);
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

