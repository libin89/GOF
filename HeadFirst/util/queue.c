#include "queue.h"


listNode *inQueue(struct queueList *queue, listNode *node)
{
    if (!node) {
        printf("Null pointer.\n");
        return NULL;
    }
    
    if (queue->size) {
        node->prev = queue->tail;
        node->next = NULL;
        queue->tail->next = node;
        queue->tail = node;
    } else {
        queue->head = queue->tail = node;
        node->prev = node->next = NULL;
    }

    ++queue->size;
    return node;
}

listNode *outQueue(struct queueList *queue)
{
    if (!queue) {
        printf("Queue is null pointer.\n");
        return NULL;
    }
    listNode *node = queue->head;

    if (!queue->size) {
        printf("queue size is 0, can not pop a node.\n");
        return NULL;
    }

    if (--queue->size) {
        (queue->head = node->next)->prev = NULL;
    } else {
        queue->head = queue->tail = NULL;
    }
    node->next = node->prev = NULL;

    return node;
}


listNode *newQueueNode(void *data)
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
queueList *newQueue(void (*func)(void *data))
{
    queueList *list = NULL;

    if(!(list = (queueList *)malloc(sizeof(queueList)))) {
        printf("malloc error.\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->func = func;
    list->inQueue = inQueue;
    list->outQueue = outQueue;

    return list;
}
void deleteQueue(queueList *list)
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

#ifdef QUEUE
typedef struct s {
        int i;
        char j;
} s;
int main(void)
{
    s test[3];
    test[0].i = -10;
    test[0].j = 12;
    test[1].i = 34;
    test[1].j = 70;
    doublyLinkedList *list = newList(NULL);
    
    list->push(list, newListNode(&test[0]));
    list->push(list, newListNode(&test[1]));

    listNode *node = NULL;
    for(int i = 0; i < list->size; i++) {
        node = list->get(list, i);
        printf("get node %d\n", ((struct s *)node->data)->i);
    }

    char key = 70;
    //printf("offset j %d\n", offsetof(s, j));
    //node = list->find(list, offsetof(s, j), &key, sizeof(char), 0, NULL, 0);
    //printf("find node %d\n", ((struct s *)node->data)->i);
    //list->removeNode(list, node);
    list->removeNodeV2(list, offsetof(s, j), &key, sizeof(char));
    for(int i = 0; i < list->size; i++) {
        node = list->get(list, i);
        printf("get node %d\n", ((struct s *)node->data)->i);
    }

    return 0;
}
#endif