extern void __VERIFIER_error() __attribute__ ((__noreturn__));

#include <pthread.h>

int i=1, j=1;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

#define NUM 5

void *
t1(void* arg)
{
  int k = 0;

  for (k = 0; k < NUM; k++)
  {
    pthread_mutex_lock (&m);
    i+=j;
    pthread_mutex_unlock (&m);
  }

  pthread_exit(NULL);
}

void *
t2(void* arg)
{
  int k = 0;

  for (k = 0; k < NUM; k++)
  {
    pthread_mutex_lock (&m);
    j+=i;
    pthread_mutex_unlock (&m);
  }
  pthread_exit(NULL);
}

int
main(int argc, char **argv)
{
  pthread_t id1, id2;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  if (i >= 144 || j >= 144) {
    ERROR: __VERIFIER_error();
  }

  pthread_join (id1,0);
  pthread_join (id2,0);

  return 0;
}

