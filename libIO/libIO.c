#include<stdio.h>
#include<string.h>

int main()
{
    FILE* fp=NULL;
    fp=fopen("./test.txt","r+");
    if(fp==NULL){
        perror("fopen error\n");
        return -1;
    }
    //fseek跳转读写位置 SEEK_SET-从文件起始位置偏移  SEEK_END-从文件末尾位置开始偏移  SEEK_CUR-从文件当前位置开始偏移
    fseek(fp,0,SEEK_END);//将文件的读写位置偏移到末尾--偏移量也可以是负值，表示向前偏移
    char* ptr="It is a fine day today.\n";
    int ret =fwrite(ptr,strlen(ptr),1,fp);//(数据，块大小，块个数，文件流指针)
    if(ret==0){
        perror("fwrite error\n");
        return -1;
    }
    printf("ret:%d\n",ret);

    fseek(fp,0,SEEK_SET);//将文件的读写位置偏移到末尾--偏移量也可以是负值，表示向前偏移
    char tmp[1024]={0};
    ret=fread(tmp,1,1023,fp);
    printf("ret:%d-[%s]\n",ret,tmp);
    fclose(fp);
    return 0;
}
