#include"heap.h"



void HeapPrint(struct Heap* hp)
{
    assert(hp);
    printf("Heap:");
    for(int i=0;i<hp->_size;++i){
        printf("%d ",hp->_a[i]);
    }
    printf("\n");
}
void swap(HeapDataType* e1,HeapDataType* e2)
{
    HeapDataType tmp=*e1;
    *e1=*e2;
    *e2=tmp;
}
void AdjustUp(HeapDataType* a,int child)
{
    assert(a);
    int parent=(child-1)/2;
    while(child>0){
        if(a[child]<a[parent]){
            swap(&a[child],&a[parent]);
            child=parent;
            parent=(child-1)/2;
        }else{
            break;
        }
    }
}
void AdjustDown(HeapDataType* a,int parent,int n)
{
    assert(a);
    int child=2*parent+1;
    while(child<n){
        if(child+1<n && a[child+1]<a[child]){
            child++; 
        }
        if(a[child]<a[parent]){
            swap(&a[child],&a[parent]);
            parent=child;
            child=2*parent+1;
        }else{
            break;
        }
    }
}
void HeapInit(struct Heap* hp,HeapDataType* arr,int n)
{
    assert(hp);
    hp->_a=(HeapDataType*)malloc(sizeof(HeapDataType)*n);
    if(hp->_a==NULL){
        perror("HeapInit Fail!\n");
        exit(-1);
    }
    memcpy(hp->_a,arr,sizeof(HeapDataType)*n);
    hp->_capacity=hp->_size=n; 
    for(int i=(hp->_size-2)/2;i>=0;--i){
        AdjustDown(hp->_a,i,hp->_size);
    }
}
void HeapDestroy(struct Heap* hp)
{
    assert(hp);
    free(hp->_a);
    hp->_a=NULL;
    hp->_size=hp->_capacity=0;
}
void HeapPush(struct Heap* hp,HeapDataType val)
{
    assert(hp);
    if(hp->_size==hp->_capacity){
        HeapDataType* tmp=(HeapDataType*)realloc(hp->_a,sizeof(HeapDataType)*hp->_capacity*2);
        if(tmp==NULL){
            perror("HeapPush realloc fail!\n");
            exit(-1);
        }
        hp->_a=tmp;
        hp->_capacity*=2;
    } 
    hp->_a[hp->_size]=val;
    hp->_size++;
    AdjustUp(hp->_a,hp->_size-1);
}
void HeapPop(struct Heap* hp)
{
    assert(hp);
    assert(hp->_size);
    swap(&hp->_a[0],&hp->_a[hp->_size-1]);
    hp->_size--;
    AdjustDown(hp->_a,0,hp->_size);
}
HeapDataType HeapTop(struct Heap* hp)
{
    assert(hp);
    return hp->_a[0];
}
int HeapSize(struct Heap* hp)
{
    assert(hp);
    return hp->_size;
}
bool HeapEmpty(struct Heap* hp)
{
    assert(hp);
    return hp->_size==0;
}
