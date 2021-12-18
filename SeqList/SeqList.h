#pragma once

typedef int SeqListData; 
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>


struct SeqL
{
    SeqListData *_a;
    int _size;
    int _capacity;
};

void SeqLInit(struct SeqL *seq);
void SeqLPrint(struct SeqL *seq);
int GetSeqListSize(struct SeqL *seq);
void SeqLPushBack(struct SeqL *seq,SeqListData x);
void SeqLPushFront(struct SeqL *seq,SeqListData x);
void SeqLPopBack(struct SeqL *seq);
void SeqLPopFront(struct SeqL *seq);
void SeqLInsert(struct SeqL *seq,SeqListData x,int pos);
void SeqLPop(struct SeqL *seq,int pos);
void SeqLDestroy(struct SeqL* seq);
