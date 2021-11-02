#include"qsnonr.h"


typedef char STDataType;
struct Stack
{
	STDataType* a;
	int top;
	int capacity;
};
void StackInit(struct Stack* st)
{
	st->a = (STDataType*)malloc(sizeof(STDataType) * 4);
	if (st->a == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	st->capacity = 4;
	st->top = 0;
}
void StackPush(struct Stack* st, STDataType x)
{
	assert(st);
	if (st->top == st->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(st->a, st->capacity * 2 * sizeof(STDataType));
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		st->a = tmp;
		st->capacity *= 2;
	}
	st->a[st->top] = x;
	st->top++;
}
void StackPop(struct Stack* st)
{
	assert(st);
	assert(st->top > 0);
	st->top--;
}
STDataType StackTop(struct Stack* st)
{
	assert(st);
	assert(st->top > 0);
	return st->a[st->top - 1];
}
bool StackEmpty(struct Stack* st)
{
	assert(st);
	return st->top == 0;
}
int StackSize(struct Stack* st)
{
	assert(st);
	return st->top;
}
void StackDestroy(struct Stack* st)
{
	assert(st);
	free(st->a);
	st->a = NULL;
}
void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("\n");
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
void QuickSortNonR(int* a, int left, int right)
{
	assert(a);
	struct Stack st;
	StackInit(&st);
	StackPush(&st, right);
	StackPush(&st, left);
	while (!StackEmpty(&st))
	{
		int begin = StackTop(&st);
		StackPop(&st);
		int end = StackTop(&st);
		StackPop(&st);
		int div = PartSort3(a, begin, end);
		if (div + 1 < end)
		{
			StackPush(&st, end);
			StackPush(&st, div + 1);
		}
		if (begin < div - 1)
		{
			StackPush(&st, div - 1);
			StackPush(&st, begin);
		}
	}
	StackDestroy(&st);
}
