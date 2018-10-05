
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   //for exit
#include <pthread.h>  //for pthread_create
#include <unistd.h>   //for sleep

int thread_finished;

void *fun(void *m)
{
    printf("iam in thread function\n");
    printf("recv=%s\n",(char *)m);
    sleep(4);
    printf("Second thread setting finished flag, and exiting now\n");
    thread_finished = 1;
    pthread_exit(NULL);
}
int main()
{
    pthread_t tid;
    pthread_attr_t t_attr;
    int res;
    char msg[]="pthread attributes";

    res=pthread_attr_init(&t_attr);
    if(res!=0)
    {
         printf("attribute creation is failed\n");
         //exit(1);
    } 
  
    //for thread is set to detaching state

    res=pthread_attr_setdetachstate(&t_attr,PTHREAD_CREATE_DETACHED);
    if(res!=0)
    {
         printf("setting detached attribute is failed\n");
         //exit(1);
    }
   
    //for thread creation

    res=pthread_create(&tid,0,fun,(void *)msg);
    if(res!=0)
    {
         printf("thread creation is failed\n");
         exit(1);
    }
    
    //waiting for until thread created function is terminated
    
    pthread_join(tid,NULL);
    pthread_attr_destroy(&t_attr);

    printf("Other thread finished, bye!\n");
    return 0;
}
