#ifndef _DOUBLYLISTEDLIST_H
#define _DOUBLYLISTEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LIST_HEAD,
    LIST_TAIL
} listDirection;

typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *data;
} listNode;

typedef struct doublyLinkedList {
    struct listNode *head;
    struct listNode *tail;
    int size;
    void (*func)(void *data); //reserved
    listNode *(*push)(struct doublyLinkedList *list, listNode *node);
    listNode *(*pop)(struct doublyLinkedList *list, listNode *node);
    void (*remove)(struct doublyLinkedList *list, listNode *node);
    void (*removeV2)(struct doublyLinkedList *list, int offset,\
            void *data, int bytes);
    listNode *(*find)(struct doublyLinkedList *list, int offsetMatch, void *match,\
            int lenMatch, int offsetExclude, void *exclude, int lenExclude);
    listNode *(*get)(struct doublyLinkedList *list, int index);
} doublyLinkedList;

listNode *newListNode(void *data);
doublyLinkedList *newList(void (*func)(void *data)); //if no func parameter, use NULL.
void deleteList(doublyLinkedList *list);

#endif