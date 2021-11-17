#include"Stack.h"
int main()
{
    struct Stack st;
	StackInit(&st);
	StackPush(&st, 1);
	StackPush(&st, 2);
	StackPush(&st, 3);
	StackPush(&st, 4);
	StackPush(&st, 5);
	StackPop(&st);
	printf("%d\n", StackTop(&st));
	printf("%d\n", StackSize(&st));
	while (!StackEmpty(&st))
	{
		printf("%d ", StackTop(&st));
		StackPop(&st);
	}
	printf("\n");
	if (!StackEmpty(&st))
	{
		printf("Stack 不为空\n");
	}
    else
		printf("Stack Empty\n");

	StackDestroy(&st);
	return 0;
}
