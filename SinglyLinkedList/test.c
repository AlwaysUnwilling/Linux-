#include"slist.h"


void SListTest1()
{
    struct SList *sl=NULL;
    SListPushBack(&sl,1);
    SListPushBack(&sl,2);
    SListPushBack(&sl,3);
    SListPushBack(&sl,4);
    SListPushBack(&sl,5);
    SListPushBack(&sl,6);
    SListPrint(sl);
    
    SListPushFront(&sl,-4);
    SListPushFront(&sl,-3);
    SListPushFront(&sl,-2);
    SListPushFront(&sl,-1);
    SListPushFront(&sl,0);
    SListPrint(sl);

    SListPopBack(&sl);
    SListPopBack(&sl);
    SListPopBack(&sl);
    SListPopBack(&sl);
    SListPopBack(&sl);
    SListPrint(sl);
    
    SListPopFront(&sl);
    SListPopFront(&sl);
    SListPopFront(&sl);
    SListPopFront(&sl);
    SListPopFront(&sl);
    SListPopFront(&sl);
    SListPrint(sl);
    SListDestroy(&sl);
}
void SListTest2()
{
    struct SList *s1=NULL;
    SListPushBack(&s1,1);
    SListPushBack(&s1,2);
    SListPushBack(&s1,3);
    SListPushBack(&s1,4);
    SListPushBack(&s1,5);
    SListPrint(s1);
    SListInsert(&(s1->_next),14);
    SListInsert(&(s1->_next),13);
    SListInsert(&(s1->_next),12);
    SListInsert(&(s1->_next),11);
    SListInsert(&(s1->_next),10);
    SListPrint(s1);

    if(SListFind(s1,10)){
        printf("it is true\n");
    }
    SListErease(&s1);
    SListErease(&s1);
    SListErease(&s1);
    SListErease(&s1);
    SListErease(&s1);
    SListErease(&s1);
    SListErease(&s1);
    SListErease(&s1);
    SListErease(&s1);
    SListPrint(s1);
    SListDestroy(&s1);
}
int main()
{
    //SListTest1();
    SListTest2();
    return 0;
}
