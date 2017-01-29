//#include "verifier-framac.h"
//#include "verifier-none.h"
//#include "verifier-poet.h"
#include "verifier-impara.h"
//#include "verifier-astreea.h"

#define MIN 0
#define MAX 10

pthread_mutex_t  mutex;
int data = 0;

void *thread1(void *arg)
{
  pthread_mutex_lock(&mutex);
  data++;
  printf ("t1: data %d\n", data);
  pthread_mutex_unlock(&mutex);
  return 0;
}

void *thread2(void *arg)
{
  pthread_mutex_lock(&mutex);
  data+=2;
  printf ("t2: data %d\n", data);
  pthread_mutex_unlock(&mutex);
  return 0;
}


void *thread3(void *arg)
{
  pthread_mutex_lock(&mutex);
  printf ("t3: data %d\n", data);
  //@ assert (MIN <= data);
  __VERIFIER_assert (MIN <= data);
  //@ assert (data < MAX + 3);
  __VERIFIER_assert (data < MAX + 3);
  pthread_mutex_unlock(&mutex);    
  return 0;
}


int main()
{
  pthread_mutex_init(&mutex, 0);

  pthread_t t1, t2, t3;

  data = __VERIFIER_nondet_int (MIN, MAX);
  printf ("m: MIN %d MAX %d data %d\n", MIN, MAX, data);

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);

  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  pthread_mutex_destroy(&mutex);
  return 0;
}
