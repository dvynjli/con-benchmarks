#include "verifier-impara.h"

#define NUM_THREADS 5
#define MIN 0
#define MAX 1000

pthread_mutex_t m; 

int s;

void* thr1(void* arg)
{
  int l = __VERIFIER_nondet_int(MIN, MAX);
  l = 4;

  pthread_mutex_lock (&m);
  s = l;
  __VERIFIER_assert (s == l);
  pthread_mutex_unlock (&m);

  return NULL;
}

int main()
{
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

