#include <assert.h>
#include <pthread.h>

int x = 0;
int y = 0;
pthread_mutex_t m;

void *thread (void *arg)
{
   pthread_mutex_lock (&m);
   x = 1;
   y = 1;
   pthread_mutex_unlock (&m);

   return 0;
}

int main ()
{
   //void *p;
   pthread_t t;

   pthread_mutex_init (&m, 0);
   pthread_create (&t, 0, thread, 0);

   pthread_mutex_lock (&m);
   x = 2;
   y = 2;
   pthread_mutex_unlock (&m);

   pthread_mutex_lock (&m);
   assert (x == y);
   pthread_mutex_unlock (&m);

   //pthread_join (t, &p);
   return 0;
}
