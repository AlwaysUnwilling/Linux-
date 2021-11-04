#include"mergesortnonr.h"


void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("\n");
}
void MergeArray(int* a, int begin1, int end1, int begin2, int end2, int* tmp)
{
	int left = begin1, right = end2;
	//归并[left,mid]和[mid+1,right]有序
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}
	while (begin1 <= end1)
		tmp[index++] = a[begin1++];
	while (begin2 <= end2)
		tmp[index++] = a[begin2++];
	//归并完成后把归并好的数据从tmp拷贝回原数组
	for (int i = left; i <= right; i++)
		a[i] = tmp[i];
}
void MergeSortNonR(int* a, int n)
{
	assert(a);
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			//[i,i+gap-1]  [i+gap,i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//1.合并时只有第一组,第二组不存在，就不需要合并
			if (begin2 >= n)
				break;
			//2.合并时第二组只有部分数据，需要修正end2边界
			if (end2 >= n)
				end2 = n - 1;

			MergeArray(a, begin1, end1, begin2,  end2, tmp);
		}
		//PrintArray(a, n);
		gap *= 2;
	}
	free(tmp);
	tmp = NULL;
}
