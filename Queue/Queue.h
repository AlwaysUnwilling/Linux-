#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>

typedef int QDataType;
struct QueueNode
{
	struct QueueNode* next;
	QDataType data;
};
struct Queue
{
	struct QueueNode* head;
	struct QueueNode* tail; 
};

void QueueInit(struct Queue* pq);//初始化
void QueueDestroy(struct Queue* pq);//销毁
void QueuePush(struct Queue* pq, QDataType x);//队尾入（尾插）
void QueuePop(struct Queue* pq);//队头出（头删）
QDataType QueueFront(struct Queue* pq);//取头数据
QDataType QueueBack(struct Queue* pq);//取队尾数据
int QueueSize(struct Queue* pq);//输出队列大小
bool QueueEmpty(struct Queue* pq);//判空
