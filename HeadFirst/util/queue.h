#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#ifndef offsetof
#define offsetof(TYPE, MEMBER) (size_t)&(((TYPE *)0)->MEMBER)
#endif

typedef enum {
    LIST_HEAD,
    LIST_TAIL
} listDirection;

typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *data;
} listNode;

typedef struct queueList {
    struct listNode *head;
    struct listNode *tail;
    int size;
    void (*func)(void *data); //reserved
    listNode *(*inQueue)(struct queueList *queue, listNode *node);
    listNode *(*outQueue)(struct queueList *queue);
} queueList;

listNode *newQueueNode(void *data);
queueList *newQueue(void (*func)(void *data)); //if no func parameter, use NULL.
void deleteQueue(queueList *queue);

#endif