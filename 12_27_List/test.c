#include"list.h"



void ListTest1()
{
    struct List* ls=NULL;
    ListInit(&ls);
    ListPushBack(ls,1);
    ListPushBack(ls,2);
    ListPushBack(ls,3);
    ListPushBack(ls,4);
    ListPushBack(ls,5);
    ListPushBack(ls,6);
    ListPrint(ls);
    ListPopBack(ls);
    ListPrint(ls);
    ListPopBack(ls);
    ListPrint(ls);
    ListPopBack(ls);
    ListPrint(ls);
    ListPopBack(ls);
    ListPrint(ls);
    ListPopBack(ls);
    ListPrint(ls);
    ListPopBack(ls);
    ListPrint(ls);
    printf("\n##########ListFrontTest#############\n"); 
    ListPushFront(ls,6);
    ListPrint(ls);
    ListPushFront(ls,5);
    ListPrint(ls);
    ListPushFront(ls,4);
    ListPrint(ls);
    ListPushFront(ls,3);
    ListPrint(ls);
    ListPushFront(ls,2);
    ListPrint(ls);
    ListPushFront(ls,1);
    ListPrint(ls);
    ListPushFront(ls,0);
    ListPrint(ls);
    printf("\n############ListPopFrontTest#########\n");
    ListPopFront(ls);
    ListPrint(ls);
    ListPopFront(ls);
    ListPrint(ls);
    ListPopFront(ls);
    ListPrint(ls);
    ListPopFront(ls);
    ListPrint(ls);
    ListPopFront(ls);
    ListPrint(ls);
    ListPopFront(ls);
    ListPrint(ls);
    ListPopFront(ls);
    ListPrint(ls);
    printf("\n##############ListInsertTest###########\n");
    ListInsert(ls->_next,6);
    ListPrint(ls);
    ListInsert(ls->_next,5);
    ListPrint(ls);
    ListInsert(ls->_next,4);
    ListPrint(ls);
    ListInsert(ls->_next,3);
    ListPrint(ls);
    ListInsert(ls->_next,2);
    ListPrint(ls);
    ListInsert(ls->_next,1);
    ListPrint(ls);
    ListInsert(ls->_next,0);
    ListPrint(ls);
    struct List* ret=ListFind(ls,2);
    printf("ret:%p\n",ret);
    ListInsert(ret,7);
    ListPrint(ls);
    printf("\n##########ListEraseTest#############\n"); 
    struct List* ret1=ListFind(ls,7);
    printf("ret1:%p\n",ret1);
    ListErase(ret1);
    ListPrint(ls);
    ListDestroy(&ls);

}
int main()
{
    ListTest1();
    return 0;
}
