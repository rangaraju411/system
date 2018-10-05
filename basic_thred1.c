
#include <stdio.h>   //for printf and scanf
#include <stdlib.h>  //for exit
#include <pthread.h> //for phtread_create,pthread_join

//once thread is created after that it is called to this function

void *mythread(void *v)
{
    int *p=(int *)v;
    printf("iam in thread%d\n",*p);
    printf("thread id=%u\n",(unsigned int)pthread_self());
    return NULL;
}

int main()
{
    int i;
    pthread_t tid;

    //for thread creation
           
    printf("before thread create\n");
    for(i=0;i<3;i++)
    pthread_create(&tid,0,mythread,(void *)&i);
   
    //waiting for until thread created function is terminated
    
    pthread_join(tid,NULL);
    printf("after thread create\n");
}

