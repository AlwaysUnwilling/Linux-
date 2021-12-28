#pragma once


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

typedef int HeapDataType;
struct Heap
{
    HeapDataType* _a;
    int _size;
    int _capacity;
};

void HeapInit(struct Heap* hp,HeapDataType* arr,int n);
void HeapDestroy(struct Heap* hp);
void HeapPush(struct Heap* hp,HeapDataType val);
void HeapPop(struct Heap* hp);
HeapDataType HeapTop(struct Heap* hp);
int HeapSize(struct Heap* hp);
bool HeapEmpty(struct Heap* hp); 
void HeapPrint(struct Heap* hp);
