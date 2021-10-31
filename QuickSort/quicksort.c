#include"quicksort.h"

void PrintArray(int* a,int n)
{
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}
void InsertSort(int* a,int n)
{
    assert(a);
    for(int i=0;i<n-1;i++){
        int end=i;
        int tmp=a[end+1];
        while(end>=0){
            if(tmp<a[end]){
                a[end+1]=a[end];
                end--;
            }
            else{
                break;
            }
        }
        a[end+1]=tmp;
    }
}
void Swap(int* element1, int* element2)
{
	int tmp = *element1;
	*element1 = *element2;
	*element2 = tmp;
}
int GetMidIndex(int* a, int begin, int end)
{
	assert(a);
	int mid = (begin + end) / 2;
	if (a[begin] > a[mid])
	{
		if (a[mid] > a[end])
			return mid;
		else if (a[end] < a[begin])
			return end;
		else
			return begin;
	}
	else
	{
		if (a[begin] > a[end])
			return begin;
		else if (a[end] < a[mid])
			return end;
		else
			return mid;
	}
}
int PartSort3(int* a, int begin, int end)
{
	Swap(&a[GetMidIndex(a, begin, end)], &a[end]);
	int key = a[end];
	//int prev = 0;
	//int cur = 0;
	//while (cur <= end)
	//{
	//	while (cur <= end && a[cur] > key)
	//		++cur;

	//	Swap(&a[prev], &a[cur]);
	//	++prev;
	//	++cur;
	//}
	//return prev-1;

	int cur = begin;
	int prev = begin - 1;
	while (cur < end)
	{
		if (a[cur] < key && ++prev != cur)
			Swap(&a[prev], &a[cur]);
		++cur;
	}
	Swap(&a[++prev], &a[cur]);
	return prev;
}
void QuickSort(int* a,int left,int right)
{
    assert(a);
    if(left>=right){
        return;
    }
    if(right-left+1>10){
        int divindex=PartSort3(a,left,right);
        QuickSort(a,left,divindex-1);
        QuickSort(a,divindex+1,right);
    }
    else{
        InsertSort(a+left,right-left+1);
    }
}

