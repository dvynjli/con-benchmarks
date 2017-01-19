#include "mthread_pthread.h"

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                      void *(*start_routine)(void *), void *arg) {
  int result = __FRAMAC_THREAD_CREATE(thread, start_routine, arg);
  if (result > 0) {
    *thread=result;
    __FRAMAC_THREAD_START(result);
    return 0; }
  else { return 11; /* EAGAIN */ }
}

int pthread_cancel(pthread_t thread) {
  int result = __FRAMAC_THREAD_CANCEL(thread);
  return (result != -1 ? 0 : 3 /* ESRCH */);
}

pthread_t pthread_self(void) {
  return __FRAMAC_THREAD_ID();
}

int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr) {
  int result = __FRAMAC_MUTEX_INIT(mutex);
  if (result > 0) { *mutex = result; return 0; }
  else { return 22; /* EINVAL */}
}

int pthread_mutex_lock (pthread_mutex_t *mutex) {
  int result = __FRAMAC_MUTEX_LOCK(*mutex);
  return (result != -1 ? 0 : 22 /* EINVAL */);
}

int pthread_mutex_trylock (pthread_mutex_t *mutex) {
  int result = __FRAMAC_MUTEX_LOCK(*mutex);
  return (result != -1 ? 0 : 22 /* EINVAL */);
}

int pthread_mutex_unlock (pthread_mutex_t * mutex ) {
  int result = __FRAMAC_MUTEX_UNLOCK(*mutex);
  return (result != -1 ? 0 : 22 /* EINVAL */);
}

/* ==========================================*/
/* Functions currently not perfectly stubbed */

// Does not store the return code
void pthread_exit(void *thread_return) {
  __FRAMAC_THREAD_EXIT(thread_return);
}

extern volatile int NON_DET_JOIN;
// Overapproximated return code for the function and the joined threads
int pthread_join(pthread_t thread, void **retval) {
  if (retval) *retval = NON_DET_JOIN;
  return NON_DET_JOIN ? -1 : 0;
}

/* ================================*/
/* Stubs that do nothing */

int pthread_setcancelstate(int state, int *oldstate) {
  return 0;
}

int pthread_setcanceltype(int type, int *oldtype) {
  return 0;
}

void pthread_testcancel(void) {
}
