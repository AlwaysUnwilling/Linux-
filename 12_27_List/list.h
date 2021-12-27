#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


typedef int  ListData;

struct List
{ 
    struct List* _prev;
    struct List* _next;
    ListData _val;
};


void ListInit(struct List** ls);
struct List* ListNodeCreate(ListData val);
void ListPrint(struct List* ls);
void ListPushBack(struct List* ls,ListData val);
void ListPopBack(struct List* ls);
void ListPushFront(struct List* ls,ListData val);
void ListPopFront(struct List* ls);
struct List* ListFind(struct List* ls,ListData val);
void ListInsert(struct List* pos,ListData val);
void ListErase(struct List* pos);
void ListDestroy(struct List** ls);
