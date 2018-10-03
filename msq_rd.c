
#include <unistd.h>    //for sleep
#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit
#include <sys/msg.h>   //for msgget and msgsnd

struct msg
{
    long mtype;//don't place int instead of long it will not work
    char mtext[100];
}rcv;

int main()
{
    long  mid;
    int msqid;
    key_t key=0x20;
    
    //for creating message queue using msgget and check it is created or not

    msqid=msgget(key,IPC_CREAT|0666);
    if(msqid<0)
    {
         perror("msgqueue is not created");
         exit(1);
    }
    //printf("enter mtype");
    //scanf("%ld",&mid);
    
    //Receiving message using msgrcv

    msgrcv(msqid,&rcv,sizeof(rcv.mtext),1,0);
    printf("%s",rcv.mtext);

    //msgctl() performs the control operation specified by cmd on the System V      message queue with identifier msqid. 

    msgctl(msqid,IPC_RMID,0);
}

