#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>


#define FIFL_PATH "/home/Lg/myGit/Linux-/3_20_Review"

#define KEY (ftok(FIFL_PATH,84129762))
#define SIZE 4096
