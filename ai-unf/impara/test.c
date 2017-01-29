#include <pthread.h>
#include <assert.h>

int nondet();

int i;
pthread_mutex_t m;

void* foo(void *arg)
{
  pthread_mutex_lock(&m);
  if (i > 0)
  {
    i=0;
  } else 
  {
    i+=10;
  }
  pthread_mutex_unlock(&m);
  return 0;
}

int main()
{
  i = nondet();
  __CPROVER_assume (i >= 0);
  __CPROVER_assume (i <= 1024);

  pthread_mutex_init(&m, NULL);
  pthread_t th1, th2, th3;
  pthread_create(&th1, 0, foo, 0);
  pthread_create(&th2, 0, foo, 0);
  pthread_create(&th3, 0, foo, 0);
  pthread_join(th1, 0);
  pthread_join(th2, 0);
  pthread_join(th3, 0);

  assert(i>= 0); // should pass
  assert(i<= 10); // should pass
  return 0;
}
