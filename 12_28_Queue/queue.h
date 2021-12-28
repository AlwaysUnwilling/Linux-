#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


typedef int QueueDataType;

struct QueueNode
{
    struct QueueNode* _next;
    QueueDataType _val;
};
struct Queue
{
    struct QueueNode* _head;
    struct QueueNode* _tail;
};

void QueueInit(struct Queue* q);
void QueueDestroy(struct Queue* q);

void QueuePush(struct Queue* q,QueueDataType val);
void QueuePop(struct Queue* q);
QueueDataType QueueFront(struct Queue* q);
QueueDataType QueueBack(struct Queue* q);

bool QueueEmpty(struct Queue* q);
int QueueSize(struct Queue* q); 
