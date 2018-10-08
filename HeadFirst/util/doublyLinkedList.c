#include "doublyLinkedList.h"

int isFullZero(char *val, int nBytes)
{
  while( nBytes >= 0 ) {
    if (val[nBytes--] != '\0')
      return 0;
  }
   
   return 1;
}

listNode *rightPush(struct doublyLinkedList *list, listNode *node)
{
    if (!node) {
        printf("Null pointer.\n");
        return NULL;
    }
    
    if (list->size) {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    } else {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }

    ++list->size;
    return node;
}
listNode *leftPush(struct doublyLinkedList *list, listNode *node)
{
    if (!node) {
        printf("Null pointer.\n");
        return NULL;
    }
        
    if (list->size) {
        node->next = list->head;
        node->prev = NULL;
        list->head->prev = node;
        list->head = node;
    } else {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }

    ++list->size;
    return node;
}
listNode *rightPop(struct doublyLinkedList *list)
{
    if (!list) {
        printf("List is null pointer.\n");
        return NULL;
    }
    listNode *node = list->tail;

    if (!list->size) {
        printf("list size is 0, can not pop a node.\n");
        return NULL;
    }

    if (--list->size) {
        (list->tail = node->prev)->next = NULL;
    } else {
        list->head = list->tail = NULL;
    }
    node->next = node->prev = NULL;

    return node;
}
listNode *leftPop(struct doublyLinkedList *list)
{
    if (!list) {
        printf("List is null pointer.\n");
        return NULL;
    }
    listNode *node = list->head;

    if (!list->size) {
        printf("list size is 0, can not pop a node.\n");
        return NULL;
    }

    if (--list->size) {
        (list->head = node->next)->prev = NULL;
    } else {
        list->head = list->tail = NULL;
    }
    node->next = node->prev = NULL;

    return node;
}
void remove(struct doublyLinkedList *list, listNode *node)
{
    if (!node) {
        printf("node is null.\n");
        return;
    }

    node->prev\
        ? (node->prev->next = node->next)\
        : (list->head = node->next);

    node->next\
        ? (node->next->prev = node->prev)\
        : (list->tail = node->prev);
    
    if (list->func)
        list->func(node->data);
    
    free(node);
    --list->size;
}
void removeV2(struct doublyLinkedList *list, int offset,\
            void *data, int bytes)
{
    listNode *node = list->head;

    while (node) {
        if (isFullZero(((char *)node->data + offset), bytes) == 0\
            && memcmp(data, ((char *)node->data + offset), bytes) == 0)
            list->remove(list, node);
        node = node->next;
    }
}
listNode *find(struct doublyLinkedList *list, int offsetMatch, void *match,\
            int lenMatch, int offsetExclude, void *exclude, int lenExclude)
{
    listNode *node = list->head;

    while (node) {
        if (match != NULL && memcmp(match, ((char *)node->data + offsetMatch), lenMatch)\
            == 0) {
            if ((exclude == NULL) || (exclude != NULL\
                && memcmp(exclude, ((char*)node->data+offsetExclude), lenExclude) != 0))
                return node;
        }
        node = node->next;
    }

    return NULL;
}
listNode *get(struct doublyLinkedList *list, int index)
{
    listDirection direction = LIST_HEAD;
    listNode *node = list->head;

    if (index < 0) {
        direction = LIST_TAIL;
        index = -index;
    }

    if (index < list->size) {
        if (direction == LIST_HEAD)
            while (index--) node = node->next;
        else
            while (index--) node = node->prev;

        return node;
    }

    return NULL;
}

listNode *newListNode(void *data)
{
    listNode *node = NULL;

    if(!(node = (listNode *)malloc(sizeof(listNode)))) {
        printf("malloc error.\n");
        return NULL;
    }
    node->prev = NULL;
    node->next = NULL;
    node->data = data;

    return node;
}
doublyLinkedList *newList(void (*func)(void *data))
{
    doublyLinkedList *list = NULL;

    if(!(list = (doublyLinkedList *)malloc(sizeof(doublyLinkedList)))) {
        printf("malloc error.\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->func = func;
    list->push = rightPush;
    list->pop = rightPop;
    list->remove = remove;
    list->removeV2 = removeV2;
    list->find = find;
    list->get = get;

    return list;
}
void deleteList(doublyLinkedList *list)
{
    listNode *next = NULL;
    listNode *node = list->head;

    while(node) {
        next = node->next;
        if (list->func)
            list->func(node->data);
        free(node);
        node = next;
    }
    free(list);
}