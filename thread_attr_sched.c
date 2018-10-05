
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   //for exit
#include <pthread.h>  //for pthread_create
#include <unistd.h>   //for sleep

int max_priority,min_priority;
int thread_finished;

//once thread is created it is called this function

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
    struct sched_param scheduling_value;
    int res,p;
    char msg[]="pthread attributes";

    //initializing thread attribute

    res=pthread_attr_init(&t_attr);
    if(res!=0)
    {
         printf("attribute creation is failed\n");
         exit(1);
    }
    
    //set thread sched policy like SCHED_OTHER,SCHED_FIFO

    res = pthread_attr_setschedpolicy(&t_attr, SCHED_OTHER);
    if (res != 0) 
    {
         perror("Setting scheduling policy failed");
         exit(1);
    }
    
    //receiving thread min and max priority values of SCHED_OTHER

    max_priority = sched_get_priority_max(SCHED_OTHER);
    min_priority = sched_get_priority_min(SCHED_OTHER);
    scheduling_value.sched_priority = min_priority;
    printf("max=%d,min=%d\n",max_priority,min_priority);
   
    //set thread scheduling parameters

    res = pthread_attr_setschedparam(&t_attr, &scheduling_value);
    if (res != 0) 
    {
         perror("Setting scheduling priority failed");
         exit(EXIT_FAILURE);
    }  
   
    //detach the thread creation

    res=pthread_attr_setdetachstate(&t_attr,PTHREAD_CREATE_DETACHED);
    if(res!=0)
    {
         printf("setting detached attribute is failed\n");
         exit(1);
    }

    //for thread creation

    res=pthread_create(&tid,0,fun,(void *)msg);

    //set thread priority
 
    p=pthread_setschedprio(tid,max_priority);
    if(p!=0)
    {
         perror("priority sched is failed\n");
         exit(EXIT_FAILURE);
    }
    //printf("max=%d,min=%d",max_priority,min_priority);

    pthread_attr_destroy(&t_attr);

    while(!thread_finished) 
    {
	 printf("Waiting for thread to say it’s finished...\n");
	 sleep(1);
    }          
    printf("Other thread finished, bye!\n");
    return 0;
}
