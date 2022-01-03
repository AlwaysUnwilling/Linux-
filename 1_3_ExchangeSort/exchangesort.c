#include"exchangesort.h"



void PrintArray(int* a,int n)
{
    printf("ExchangeSort: ");
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void swap(int* e1,int* e2)
{
    int tmp=*e1;
    *e1=*e2;
    *e2=tmp;
}
void BubbleSort(int* a,int n)
{
    assert(a);
    for(int i=0;i<n;++i){
        int exchange=0;
        for(int j=0;j<n-i;++j){
            if(a[j]>a[j+1]){
                swap(&a[j],&a[j+1]);
                exchange=1;
            }
        }
        if(exchange==0){
            break;
        }
    }
}

int GetMidIndex(int*a ,int left,int right)
{
    int midIndex=(left+right)>>1;
    if(a[left]<a[midIndex]){
        if(a[right]<a[midIndex]){
            if(a[left]<a[right]){
                return right;
            }else{
                return left;
            }
        }else{
            return midIndex;
        }
    }else{
        if(a[right]<a[midIndex]){
            return midIndex;
        }else{
            if(a[right]<a[left]){
                return right;
            }else{
                return left;
            }
        }
    }
}

//三数取中法选key
int PartSort(int* a,int left,int right)
{
    int midIndex=GetMidIndex(a,left,right);
    swap(&a[left],&a[midIndex]);
    int key=left;
    while(left<right){
        while(left<right && a[right]>=a[key]){
            --right;
        }

        while(left<right && a[left]<=a[key]){
            ++left;
        }

        swap(&a[left],&a[right]);
    }
    swap(&a[left],&a[key]);
    return left;
}

//挖坑法
int PartSort1(int* a,int left,int right)
{
    int midIndex=GetMidIndex(a,left,right);
    swap(&a[midIndex],&a[left]);
    int hole=a[left];
    while(left<right){
        while(left<right && a[right]>=hole){
            --right;
        }
        a[left]=a[right]; 
        while(left<right && a[left]<=hole){
            ++left;  
        }
        a[right]=a[left];
    }
    a[left]=hole;
    return left;
}

//前后指针法
int PartSort2(int* a,int left,int right)
{
    int midIndex=GetMidIndex(a,left,right);
    swap(&a[midIndex],&a[left]);
    int keyi=left;
    int prev=keyi,cur=keyi+1;
    //while(cur<=right){
    //    while(cur<=right && a[cur]>=a[keyi]){
    //        ++cur;
    //    }
    //    if(cur<=right){
    //        ++prev;
    //        swap(&a[prev],&a[cur]);
    //        ++cur;
    //    }else{
    //        break;
    //    }
    //}
    while(cur<=right){
        if(a[cur]<a[keyi] && ++prev!=cur){
            swap(&a[prev],&a[cur]);
        }
        ++cur;
    }
    swap(&a[prev],&a[keyi]);
    return prev;
}

void QuickSort(int* a,int begin,int end)
{
    assert(a);
    if(begin>=end){
        return;
    }
    if(end-begin>20){ 
        //int meetIndex=PartSort(a,begin,end);
        //int meetIndex=PartSort1(a,begin,end);
        int meetIndex=PartSort2(a,begin,end);
        //[begin,meetIndex-1]
        QuickSort(a,begin,meetIndex-1);
        //[meetIndex+1,end]
        QuickSort(a,meetIndex+1,end);
    }else{
        InsertSort(a+begin,end-begin+1);
    }
}

void QuickSortNor(int* a,int begin,int end)
{
    assert(a);
    struct Stack st;
    StackInit(&st);
    StackPush(&st,begin);
    StackPush(&st,end);
    while(!StackEmpty(&st)){
        int right=StackTop(&st);
        StackPop(&st);
        int left=StackTop(&st);
        StackPop(&st);
        int meetIndex=PartSort2(a,left,right);
        if(left<meetIndex-1){
            StackPush(&st,left);
            StackPush(&st,meetIndex-1);
        }

        if(meetIndex+1<right){
            StackPush(&st,meetIndex+1);
            StackPush(&st,right);
        }
    }
}
