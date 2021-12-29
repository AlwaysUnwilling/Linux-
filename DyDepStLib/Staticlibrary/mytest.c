#include<stdio.h>
#include"myadd.h"
#include"mysub.h"

int main()
{
    int x=10;
    int y=20;
    printf("sub:%d\n",mysub(x,y));
    printf("add:%d\n",myadd(x,y));
    printf("hello linux!\n");
    return 0;
}
