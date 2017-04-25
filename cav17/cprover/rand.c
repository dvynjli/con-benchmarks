//http://www.ibm.com/developerworks/java/library/j-jtp11234/
//Listing 5. Implementing a thread-safe PRNG with synchronization and atomic variables

#include "verifier-impara.h"

#define NUM_THREADS 5
#define MIN 0
#define MAX 1000
#define NUM 10

pthread_mutex_t m; 

int seed = 1;

void* thr1(void* arg){
  // res = PseudoRandomUsingAtomic_nex();
  int nex, nexts, casret, nex_return, nC_return;
  casret = 0;

  while(casret == 0) {
    pthread_mutex_lock (&m);
    nex = seed;
    pthread_mutex_unlock (&m);
   
    // nexts = nC(nex);
    nC_return = __VERIFIER_nondet_int (MIN, MAX);

    while (nC_return == nex || nC_return == 0)
    {
      nC_return = __VERIFIER_nondet_int(MIN, MAX);
    }
    nexts = nC_return; 
    
    pthread_mutex_lock (&m);
    // casret = __VERIFIER_atomic_CAS(nex,nexts);
    if (seed == nex)
    {
      seed = nexts; casret = 1;
    }
    else
    {
      casret = 0;
    }
    pthread_mutex_unlock (&m);
  }
 
  if (nexts < NUM)
  {
    nex_return = nexts;
  }
  else 
  {
    nex_return = NUM;
  }

  __VERIFIER_assert (nex_return <= NUM);

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

