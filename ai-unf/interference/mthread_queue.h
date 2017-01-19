#ifndef _FRAMAC_QUEUE_H_
#define _FRAMAC_QUEUE_H_

#include <mthread.h>

typedef int   msgqueue_t;

int queuecreate(framac_mthread_name* q, int size);
int msgsnd(int msgqid, const char *mess, int size);
int msgrcv(int msgqid, int size, char* mess);

#endif
