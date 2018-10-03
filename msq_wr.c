
#include <string.h>    //for strlen
#include <unistd.h>    //for sleep
#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit
#include <sys/msg.h>   //for msgget and msgsnd

struct msg
{
    long mtype;//don't place int instead of longint will not work
    char mtext[100];
}snd;

int main()
{
    int msqid,l;
    key_t key=0x20;
    // key = ftok("path",65);
    
    //for creating message queue using msgget and check it is created or not
    
    msqid=msgget(key,IPC_CREAT|0666);
    if(msqid<0)
    {
         perror("msgqueue is not created");
         exit(1);
    }
       
    snd.mtype=1;
    //printf("enter mtype:");
    //scanf("%ld",&snd.mtype);
    printf("enter text:");
    scanf("%s",snd.mtext);
    l=strlen(snd.mtext)+1;
    
    //sending message using msgsnd

    msgsnd(msqid,&snd,l,0);
}
