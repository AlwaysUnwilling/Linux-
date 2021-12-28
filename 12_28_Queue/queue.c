#include"queue.h"


void QueueInit(struct Queue* q)
{
    q->_head=q->_tail=NULL; 
}

void QueueDestroy(struct Queue* q)
{
    struct QueueNode* cur=q->_head;
    struct QueueNode* next=NULL;
    while(cur){
        next=cur->_next;
        free(cur);
        cur=next;
    }
    q->_head=q->_tail=NULL;
}

void QueuePush(struct Queue* q,QueueDataType val)
{
    assert(q);
    struct QueueNode* newNode=(struct QueueNode*)malloc(sizeof(struct QueueNode));
    if(newNode==NULL){
        perror("newNode malloc fail!\n");
        exit(1);
    }
    newNode->_val=val;
    newNode->_next=NULL;
    if(q->_tail==NULL){
        q->_head=newNode;
    }else{
        q->_tail->_next=newNode;
    }
    q->_tail=newNode;
}
void QueuePop(struct Queue* q)
{
    assert(q);
    if(!QueueEmpty(q)){
        if(q->_head->_next==NULL){
            q->_head=q->_tail=NULL;
        }else{
            struct QueueNode* newHead=q->_head->_next;
            free(q->_head);
            q->_head=newHead;
        }
    }
}
QueueDataType QueueFront(struct Queue* q)
{
    assert(q);
    assert(!QueueEmpty(q));
    return q->_head->_val;
}
QueueDataType QueueBack(struct Queue* q)
{
    assert(q);
    assert(!QueueEmpty(q));
    return q->_tail->_val;
}

bool QueueEmpty(struct Queue* q)
{
    assert(q);
    return q->_head==NULL;
}
int QueueSize(struct Queue* q)
{
    assert(q);
    int size=0;
    struct QueueNode* cur=q->_head;
    while(cur){
        cur=cur->_next;
        size++;
    }
    return size;
}
