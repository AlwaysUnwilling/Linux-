#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int StackDataType;
struct Stack
{
    int _capacity;
    int _top;
    StackDataType* _a;
};

void StackInit(struct Stack* st);
void StackPush(struct Stack* st,StackDataType val);
void StackPop(struct Stack* st);
void StackDestroy(struct Stack* st);
StackDataType StackTop(struct Stack* st);
bool StackEmpty(struct Stack* st);
int StackSize(struct Stack* st);

