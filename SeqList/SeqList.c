#include"SeqList.h"

void SeqLInit(struct SeqL *seq)
{
    seq->_a=(SeqListData*)malloc(sizeof(SeqListData)*4);
    if(seq==NULL){
        printf("SeqInit malloc fail!\n");
        exit(-1);
    }else{
        seq->_size=0;
        seq->_capacity=4;
    }
}

void SeqLPrint(struct SeqL *seq)
{
    assert(seq); 
    printf("SeqList:");
    for(int i=0;i<seq->_size;i++){
        printf("%d ",seq->_a[i]);    
    }
    printf("\n");
}

void GetSeqLCapacity(struct SeqL* seq)
{
    assert(seq);
    SeqListData *new_a=(SeqListData*)malloc(sizeof(SeqListData)*seq->_capacity*2);
    if(new_a==NULL){
        printf("GetSeqLCapacity malloc fail!\n");
        exit(-1);
    }
    for(int i=0;i<seq->_size;i++){
        new_a[i]=seq->_a[i];
    } 
    seq->_capacity*=2;
    free(seq->_a);
    seq->_a=new_a;
}

int GetSeqListSize(struct SeqL *seq)
{
    return seq->_size;   
}

void SeqLPushBack(struct SeqL *seq,SeqListData x)
{
   /* assert(seq);
    if(seq->_size==seq->_capacity){
        GetSeqLCapacity(seq);
    }
    seq->_a[seq->_size]=x;
    seq->_size++;*/
    SeqLInsert(seq,x,seq->_size);
}

void SeqLPushFront(struct SeqL *seq,SeqListData x)
{
    assert(seq);
    if(seq->_size==seq->_capacity){
        GetSeqLCapacity(seq);
    }
    int end=seq->_size;
    while(end>0){
        seq->_a[end]=seq->_a[end-1];
        end--;
    }
    seq->_a[end]=x;
    seq->_size++;
}
void SeqLPopBack(struct SeqL *seq)
{
    assert(seq);
    assert(seq->_size);
    seq->_size--;
}
void SeqLPopFront(struct SeqL *seq)
{
    assert(seq);
    assert(seq->_size>0);
    int front=0;
    while(front<seq->_size-1){
        seq->_a[front]=seq->_a[front+1];
        front++;
    }
    seq->_size--;
}
void SeqLInsert(struct SeqL *seq,SeqListData x,int pos)
{
    assert(seq);
    if(pos>seq->_size){
        pos=seq->_size;
    }
    if(seq->_size==seq->_capacity){
        GetSeqLCapacity(seq);
    }
    int end=seq->_size-1;
    while(end>=pos){
        seq->_a[end+1]=seq->_a[end];
        end--;
    }
    seq->_a[pos]=x;
    seq->_size++;
}
void SeqLPop(struct SeqL *seq,int pos)
{
    assert(seq);
    assert(pos>0);
    assert(seq->_size>0);
    if(pos>seq->_size){
        pos=seq->_size;
    }
    int cur=pos-1;
    while(cur<seq->_size-1){
        seq->_a[cur]=seq->_a[cur+1];
        cur++;
    }
    seq->_size--;

}
void SeqLDestroy(struct SeqL* seq)
{
    assert(seq);
    free(seq->_a);
    seq->_size=seq->_capacity=0;
}
