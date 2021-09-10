#include"cal.h"

int main()
{
    int x,y=0;
    while(1){
        printf("Please# ");
        scanf("%d %d",&x,&y);
        int ret=MyAdd(x,y);
        printf("%d+%d=%d\n",x,y,ret);
    }
}
