
#include <string.h>    //for strlen
#include <unistd.h>    //for sleep
#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit
#include <sys/msg.h>   //for msgget and msgsnd

int main()
{
    int msqid;
    key_t key=0x10;
    
    //for creating message queue using msgget and check it is created or not

    msqid=msgget(key,IPC_CREAT|0666);
    if(msqid<0)
    {
         perror("msg queue is not created");
         exit(1);
    }
    else
    printf("msg queue is created");
}
