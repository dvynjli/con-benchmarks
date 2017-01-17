#include <assert.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t m;

void *thread (void *arg)
{
   pthread_mutex_lock (&m);
   x++;
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
   assert (x == 0 || x == 1);
   x = 10;
   pthread_mutex_unlock (&m);

   //pthread_join (t, &p);
   return 0;
}
