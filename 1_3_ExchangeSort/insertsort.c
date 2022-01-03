#include"insertsort.h"



void InsertSort(int* a,int n)
{
    assert(a);
    for(int i=0;i<n-1;i++){
        int end=i;
        int tmp=a[end+1];
        while(end>=0){
            if(tmp<a[end]){
                a[end+1]=a[end];
                --end;
            }else{
                break;
            }
        }
        a[end+1]=tmp;
    }
}

void ShellSort(int* a,int n)
{
    assert(a);
    int gap=n;
    while(gap>1){
        gap=(gap/3)+1;
        for(int i=0;i<n-gap;++i){
            int end=i;
            int tmp=a[end+gap];
            while(end>=0){
                if(a[end]>tmp){
                    a[end+gap]=a[end];
                    end-=gap;;
                }else{
                    break;
                }
            }
            a[end+gap]=tmp;
        }
    }
}
