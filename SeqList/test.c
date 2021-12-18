#include"SeqList.h"

void SeqListTest1()
{
    struct SeqL seq;
    SeqLInit(&seq);
    SeqLPushBack(&seq,0);
    SeqLPushBack(&seq,1);
    SeqLPushBack(&seq,2);
    SeqLPushBack(&seq,3);
    SeqLPushBack(&seq,4);
    SeqLPushFront(&seq,-1);
    SeqLPushFront(&seq,-2);
    SeqLPushFront(&seq,-3);
    SeqLPushFront(&seq,-4);
    SeqLPushFront(&seq,-5);
    SeqLPopBack(&seq);
    SeqLPopBack(&seq);
    SeqLPopBack(&seq);
    SeqLPopBack(&seq);
    SeqLPopFront(&seq);
    SeqLPopFront(&seq);
    SeqLPopFront(&seq);
    SeqLPopFront(&seq);
    SeqLPopFront(&seq);
    SeqLPopFront(&seq);
    SeqLPushBack(&seq,10);
    SeqLPushBack(&seq,11);
    SeqLPushBack(&seq,12);
    SeqLPushBack(&seq,13);
    SeqLPushBack(&seq,14);
    SeqLPushBack(&seq,15);
    SeqLPushBack(&seq,16);

    SeqLInsert(&seq,0,2);
    SeqLInsert(&seq,1,3);
    SeqLInsert(&seq,2,4);
    SeqLInsert(&seq,3,5);
    SeqLInsert(&seq,4,6);
    SeqLPrint(&seq);

    SeqLPushBack(&seq,17);
    SeqLPushBack(&seq,18);
    SeqLPushBack(&seq,19);
    SeqLPushBack(&seq,20);
    SeqLPushBack(&seq,21);
    SeqLPrint(&seq);

    SeqLPop(&seq,1);
    SeqLPop(&seq,1);
    SeqLPop(&seq,1);
    SeqLPop(&seq,1);
    SeqLPop(&seq,1);
    SeqLPrint(&seq);


    SeqLPop(&seq,2);
    SeqLPop(&seq,2);
    SeqLPrint(&seq);

    SeqLPop(&seq,GetSeqListSize(&seq));
    SeqLPop(&seq,GetSeqListSize(&seq));
    SeqLPrint(&seq);

    SeqLDestroy(&seq);
}


int main()
{
    SeqListTest1();
    return 0;
}
