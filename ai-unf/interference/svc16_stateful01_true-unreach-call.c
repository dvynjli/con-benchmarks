//#include "verifier-framac.h"
#include "verifier-none.h"
//#include "verifier-poet.h"
//#include "verifier-astrea.h"

pthread_mutex_t ma, mb;
int data1, data2;

#ifndef VERIFIER_HAVE_PTHREAD_JOIN
pthread_mutex_t ja, jb;
int join1, join2;
#endif

void * thread1(void * arg)
{
  pthread_mutex_lock(&ma);
  data1++;
  pthread_mutex_unlock(&ma);

  pthread_mutex_lock(&ma);
  data2++;
  pthread_mutex_unlock(&ma);

#ifndef VERIFIER_HAVE_PTHREAD_JOIN
  pthread_mutex_lock(&ja);
  joina = 1;
  pthread_mutex_unlock(&ja);
#endif
  return 0;
}

void * thread2(void * arg)
{
  pthread_mutex_lock(&ma);
  data1+=5;
  pthread_mutex_unlock(&ma);

  pthread_mutex_lock(&ma);
  data2-=6;
  pthread_mutex_unlock(&ma);

#ifndef VERIFIER_HAVE_PTHREAD_JOIN
  pthread_mutex_lock(&jb);
  joinb = 1;
  pthread_mutex_unlock(&jb);
#endif
  return 0;
}

int main()
{
  pthread_t t1, t2;

  pthread_mutex_init(&ma, 0);
  pthread_mutex_init(&mb, 0);
  data1 = 10;
  data2 = 10;

#ifndef VERIFIER_HAVE_PTHREAD_JOIN
  pthread_mutex_init(&ja, 0);
  pthread_mutex_init(&jb, 0);
  join1 = join2 = 0;
#endif

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  
#ifdef VERIFIER_HAVE_PTHREAD_JOIN
  pthread_join(t1, 0);
  pthread_join(t2, 0);
#else
  pthread_mutex_lock (&ja);
  if (! joina) return 0;
  pthread_mutex_unlock (&ja);
  pthread_mutex_lock (&jb);
  if (! joinb) return 0;
  pthread_mutex_unlock (&jb);
#endif

  __VERIFIER_assert (data1 == 16);
  __VERIFIER_assert (data2 == 5);

  return 0;
}

