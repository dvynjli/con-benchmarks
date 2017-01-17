#include <assert.h>
#include <pthread.h>

int x = 123;
int msg = -1;
pthread_mutex_t m;

void *thread (void *arg)
{
   int msgloc;

   // receive msg 0 and send msg 1
   do {
      pthread_mutex_lock (&m);
      msgloc = msg;
      if (msg == 0) {
         x++;
         msg = 1;
      }
      pthread_mutex_unlock (&m);
   } while (msgloc != 0);
   return 0;
}

int ping_pong ()
{
   int msgloc;
   int xloc;
   //void *p;
   pthread_t t;

   pthread_mutex_init (&m, 0);
   pthread_create (&t, 0, thread, 0);

   // send msg 0
   pthread_mutex_lock (&m);
   msg = 0;
   x = 3;
   pthread_mutex_unlock (&m);

   // receive msg 1
   do {
      pthread_mutex_lock (&m);
      msgloc = msg;
      xloc = x;
      pthread_mutex_unlock (&m);
   } while (msgloc != 1);

   //pthread_join (t, &p);
   assert (xloc == 4);
   return 0;
}

int main ()
{
   return ping_pong ();
}
