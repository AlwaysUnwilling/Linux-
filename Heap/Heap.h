#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
typedef int HPDataType;
typedef struct Heap
{
	HPDataType* _a;
	int size;
	int capacity;
}Heap;
void HeapInit(Heap* php, HPDataType* a, int n);//初始化
void HeapDestroy(Heap* php);//销毁
void HeapPush(Heap* php, HPDataType x);
void HeapPop(Heap* php);
HPDataType HeapTop(Heap* php);
void AdjustDown(HPDataType* a, int n, int root);
void AdjustUP(HPDataType* a, int n, int child);
void Swap(HPDataType* element1, HPDataType* element2);

