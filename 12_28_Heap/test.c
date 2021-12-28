#include"heap.h"
int main()
{
	int a[] = { 27,15,19,18,28,34,65,49,25,37 };
	struct Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(HeapDataType));
    HeapPrint(&hp);
	HeapPush(&hp, 13);
    HeapPrint(&hp);
	HeapPop(&hp);
    HeapPrint(&hp);
	printf("%d\n", HeapTop(&hp));
	HeapDestroy(&hp);
	return 0;
}
