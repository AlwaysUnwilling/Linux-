#include"list.h"



void ListInit(struct List** ls)
{
    *ls=(struct List*)malloc(sizeof(struct List));
    if(ls==NULL){
        perror("ListInit Fail!\n");
        exit(1);
    }
    (*ls)->_prev=*ls;
    (*ls)->_next=*ls;
}
struct List* ListNodeCreate(ListData val)
{
    struct List* newNode=(struct List*)malloc(sizeof(struct List));
    if(newNode==NULL){
        perror("ListNodeCreate Fail!\n");
        exit(1);
    }
    newNode->_next=NULL;
    newNode->_prev=NULL;
    newNode->_val=val;
    return newNode;
}
void ListPrint(struct List* ls)
{
    assert(ls);
    struct List* cur=ls->_next;
    printf("List:");
    while(cur!=ls){
        printf("%d->",cur->_val);
        cur=cur->_next;
    }
    printf("NULL\n");
}
void ListPushBack(struct List* ls,ListData val)
{
    assert(ls);
    struct List* newNode=ListNodeCreate(val);
    struct List* tail=ls->_prev;
    tail->_next=newNode;
    newNode->_prev=tail;
    newNode->_next=ls;
    ls->_prev=newNode;
}
void ListPopBack(struct List* ls)
{
    assert(ls);
    if(ls->_prev==ls){
        printf("List is empty!\n");
        return;
    }
    struct List* tail=ls->_prev;
    struct List* prev=tail->_prev;
    prev->_next=ls;
    ls->_prev=prev;
    free(tail);
}
void ListPushFront(struct List* ls,ListData val)
{
    assert(ls);
    struct List* newNode=ListNodeCreate(val);
    struct List* next=ls->_next;
    ls->_next=newNode;
    newNode->_prev=ls;
    newNode->_next=next;
    next->_prev=newNode;
}
void ListPopFront(struct List* ls)
{
    assert(ls);
    if(ls->_next==ls){
        printf("List is empty!\n");
        return;
    }
    struct List* head=ls->_next;
    struct List* next=head->_next;
    ls->_next=next;
    next->_prev=ls;
    free(head);
}
struct List* ListFind(struct List* ls,ListData val)
{
    assert(ls);
    struct List* cur=ls->_next;
    while(cur!=ls){
        if(cur->_val==val){
            return cur;
        }
        cur=cur->_next;
    }
    return NULL;
}
void ListInsert(struct List* pos,ListData val)
{
    assert(pos);
    struct List* newNode=ListNodeCreate(val);
    struct List* prev=pos->_prev;
    prev->_next=newNode;
    newNode->_prev=prev;
    newNode->_next=pos;
    pos->_prev=newNode;
}
void ListErase(struct List* pos)
{
    assert(pos);
    struct List* prev=pos->_prev;
    struct List* next=pos->_next;
    prev->_next=next;
    next->_prev=prev;
    free(pos);
    pos=NULL;
}
void ListDestroy(struct List** ls)
{
    if((*ls)!=NULL){
        struct List* cur=(*ls)->_next;
        struct List* next=NULL;
        while(cur!=(*ls)){
            next=cur->_next;
            free(cur);
            cur=next;
        }
        free(*ls);
        *ls=NULL;
    }
}
