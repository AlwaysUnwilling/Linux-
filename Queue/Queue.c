#include"Queue.h"
void QueueInit(struct Queue* pq)//初始化
{
	assert(pq);
	pq->head = pq->tail = NULL;
}
void QueueDestroy(struct Queue* pq)//销毁
{
	assert(pq);
	struct QueueNode* cur = pq->head;
	while (cur)
	{
		struct QueueNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = pq->tail = NULL;
}
void QueuePush(struct Queue* pq, QDataType x)//队尾入（尾插）
{
	assert(pq);
	struct QueueNode* node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	if (node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	node->data = x;
	node->next = NULL;
	if (pq->head==NULL)
	{
		pq->head = pq->tail = node;
	}
	else
	{
		pq->tail->next = node;
		pq->tail = pq->tail->next;
	}
}
void QueuePop(struct Queue* pq)//队头出（头删）
{
	assert(pq);
	assert(pq->head);	
	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		struct QueueNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}
QDataType QueueFront(struct Queue* pq)//取头数据
{
	assert(pq);
	assert(pq->head);
	return pq->head->data;
}
QDataType QueueBack(struct Queue* pq)//取队尾数据
{
	assert(pq);
	assert(pq->head);
	return pq->tail->data;
}
int QueueSize(struct Queue* pq)//输出队列大小
{
	assert(pq);
	int size = 0;
	struct QueueNode* cur = pq->head;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return size;
}
bool QueueEmpty(struct Queue* pq)//判空
{
	assert(pq);
	return pq->head == NULL;
}
