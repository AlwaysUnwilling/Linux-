#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
typedef int STDataType;
typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;
void StackInit(struct Stack* ps);
void StackDestroy(struct Stack* ps);
//栈顶插入删除
void StackPush(struct Stack* ps,STDataType x);
void StackPop(struct Stack* ps);
STDataType StackTop(struct Stack* ps);  // 取栈顶的数据
int StackSize(struct Stack* ps);// 求栈的大小
bool StackEmpty(struct Stack* ps);//判断栈是否为空
