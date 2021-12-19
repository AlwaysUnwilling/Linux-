#include"slist.h"


struct SList* SListNodeCreate(SListData x)
{
    struct SList *node=(struct SList*)malloc(sizeof(struct SList));
    if(node==NULL){
        printf("SListNodeCreate node fail\n");
        exit(-1);
    }
    node->_next=NULL;
    node->_data=x;
    return node;
}

void SListPrint(struct SList* phead)
{
    struct SList *cur=phead;
    printf("SList:");
    while(cur!=NULL){
        printf("%d->",cur->_data);
        cur=cur->_next;
    }

    printf("NULL\n");
}

void SListPushBack(struct SList **phead,SListData x)
{
    struct SList* newnode=SListNodeCreate(x);
    if(*phead==NULL){
        *phead=newnode;
    }else{
        struct SList *tail=*phead;
        while(tail->_next!=NULL){
            tail=tail->_next;
        }
        tail->_next=newnode;
    }
}
void SListPushFront(struct SList **phead,SListData x)
{
    struct SList *newnode=SListNodeCreate(x);
    newnode->_next=*phead;
    *phead=newnode;
}

void SListPopBack(struct SList **phead)
{
    assert(*phead);
    if((*phead)->_next==NULL){
        free(*phead);
        *phead=NULL;
    }else{
        struct SList *tail=*phead;
        struct SList *prev=NULL;
        while(tail->_next!=NULL){
            prev=tail;
            tail=tail->_next;
        }
        free(tail);
        tail=NULL;
        prev->_next=NULL;
    }
}
void SListPopFront(struct SList **phead)
{
    assert(*phead);
    struct SList *next=(*phead)->_next;
    free(*phead);
    *phead=next;
}
void SListInsert(struct SList **pos,SListData x)
{
    assert(*pos);
    struct SList *newnode=SListNodeCreate(x);
    if((*pos)->_next==NULL){
        (*pos)->_next=newnode;
    }else{
        struct SList *next=(*pos)->_next;
        (*pos)->_next=newnode;
        newnode->_next=next;
    }

}
void SListErease(struct SList **pos)
{
    assert((*pos) && (*pos)->_next);
    struct SList *next=(*pos)->_next;
    if(next->_next==NULL){
        (*pos)->_next=NULL;
        free(next);
    }else{
        struct SList *N_next=next->_next;
        (*pos)->_next=N_next;
        free(next);
        next=NULL;
    }
}
bool SListFind(struct SList *phead,SListData x)
{
    struct SList *cur=phead;
    while(cur!=NULL){
        if(cur->_data==x){
            return true;
        }
        cur=cur->_next;
    }
    return false;
}
void SListDestroy(struct SList **phead)
{
    if(*phead!=NULL){
        struct SList *cur=(*phead)->_next;
        while(cur!=NULL){
            free(*phead);
            *phead=cur;
            cur=cur->_next;
        }    
        free(*phead);
        *phead=NULL;
    }
}
