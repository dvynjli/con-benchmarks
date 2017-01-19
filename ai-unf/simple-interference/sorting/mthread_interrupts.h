#ifndef __MTHREAD_INTERRUPTS
#define __MTHREAD_INTERRUPTS

#include "mthread.h"

framac_mthread_id __mutex_interrupts;
extern int __FRAMAC_MTHREAD_LOCK_LEVEL;
void __mthread_interrupt(void (*f)(void *), void *arg);
void __mthread_void_interrupt(void (*f)(void));
void __mthread_init_mutex_interrupt();
void __mthread_lock_interrupts();
void __mthread_unlock_interrupts();

#endif
