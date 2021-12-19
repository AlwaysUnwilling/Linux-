#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef int SListData;

struct SList
{
    SListData _data;
    struct SList* _next;
};

void SListPrint(struct SList *phead);
void SListPushBack(struct SList **phead,SListData x);
void SListPushFront(struct SList **phead,SListData x);
void SListPopBack(struct SList **phead);
void SListPopFront(struct SList **phead);
void SListInsert(struct SList **pos,SListData x);
void SListErease(struct SList **pos);
bool SListFind(struct SList *phead,SListData x);
void SListDestroy(struct SList **phead);
