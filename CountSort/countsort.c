#include"countsort.h"

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("\n");
}
void CountSort(int* a, int n)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	int range = max - min + 1;
	int* countArr = (int*)malloc(sizeof(int) * range);
	if (countArr == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	//初始化为全0
	memset(countArr, 0, sizeof(int) * range);
	for (int i = 0; i < n; i++)//统计次数
	{
		countArr[a[i] - min]++;
	}
	//排序
	int index = 0;
	for (int i = 0; i < range; i++)
	{
		while (countArr[i]--)
		{
			a[index++] = i + min;
		}
	}
	free(countArr);
	countArr = NULL;
}
