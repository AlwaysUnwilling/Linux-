#include"Stack.h"



void StackInit(struct Stack* st)
{
    st->_a=(StackDataType*)malloc(sizeof(StackDataType)*4);
    if(st->_a==NULL){
        perror("StackInit Fail!\n");
        exit(1);
    }
    st->_top=0;
    st->_capacity=4;
}
void StackCreate(struct Stack* st)
{
    assert(st);
    StackDataType* newarr=(StackDataType*)realloc(st->_a,sizeof(StackDataType)*(st->_capacity)*2);
    if(newarr==NULL){
        perror("StackCreate Fail!\n");
        exit(1);
    }
    st->_a=newarr;
    st->_capacity*=2;
}
void StackPush(struct Stack* st,StackDataType val)
{
    assert(st);
    if(st->_top==st->_capacity){
        StackCreate(st);
    }
    st->_a[st->_top]=val;
    st->_top++;
}
void StackPop(struct Stack* st)
{
    assert(st);
    assert(st->_top);
    st->_top--;
}
void StackDestroy(struct Stack* st)
{
    if(st!=NULL){
        free(st->_a);
        st->_a=NULL;
        st->_top=st->_capacity=0;
    }
}
StackDataType StackTop(struct Stack* st)
{
    assert(st && st->_top);
    return st->_a[st->_top-1];
}
bool StackEmpty(struct Stack* st)
{
    assert(st);
    return st->_top==0;
}
int StackSize(struct Stack* st)
{
    assert(st);
    return st->_top;
}
