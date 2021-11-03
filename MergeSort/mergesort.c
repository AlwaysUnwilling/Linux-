#include"mergesort.h"

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
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid+1, right, tmp);
	////归并[left,mid]和[mid+1,right]有序
	//int begin1 = left, end1 = mid;
	//int begin2 = mid+1, end2 = right;
	//int index = begin1;
	//while (begin1 <= end1 && begin2 <= end2)
	//{
	//	if (a[begin1] < a[begin2])
	//		tmp[index++] = a[begin1++];
	//	else
	//		tmp[index++] = a[begin2++];
	//}
	//while (begin1 <= end1)
	//	tmp[index++] = a[begin1++];
	//while (begin2 <= end2)
	//	tmp[index++] = a[begin2++];
	////归并完成后把归并好的数据从tmp拷贝回原数组
	//for (int i = left; i <= right; i++)
	//	a[i] = tmp[i];
	MergeArray(a, left, mid, mid + 1, right, tmp);
}
void MergeSort(int* a, int n)
{
	assert(a);
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
	tmp = NULL;
}
