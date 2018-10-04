
#include<stdio.h>    //for printf and scanf
#include<stdlib.h>   //for exit
#include<wait.h>     //for wait
#include<signal.h>   //for signal
#include<unistd.h>   //for fork,getpid,getppid
#include<pthread.h>  //for pthread create

void sigint_handler(int);

//After thread creation it is called this function

void t_handler(void *p)
{
    int t=*(int *)p;
    puts("Thread Handler\n");
    signal(SIGINT,sigint_handler);
    sleep(2);//comment this one sigint_handler is not calling//
}

//once sigint is raised signal function  called this handler

void sigint_handler(int signum)
{
    printf("signal num=%d\n",signum);
}

int main()
{
    int ret,i=1,pid;
    pthread_t tid;

    //thread creation

    pthread_create(&tid,NULL,(void *)t_handler,(void *)&i);
    sleep(2);
    pthread_kill(tid,SIGINT);
    pthread_join(tid,NULL);
 
    //process creation

    ret=fork();
    if(ret<0)
    {
         printf("process is not created\n");
         exit(1);
    }
    
    //parent process is waiting until termination of child process
   
    if(ret>0)
    {
         printf("i am in parent processid =%d\n",getppid());  
         wait(NULL);
         //kill(getpid(),SIGINT);//parent is killing child pid.
         //signal(SIGINT,sigint_handler);
    }
    
    //child process kill the parent id and raise sigint signal 
  
    else
    {
         printf("iam in child process id =%d\n",getpid());
         // 3 child is killing by Parenet pid;
         kill(getppid(),SIGINT);
         signal(SIGINT,sigint_handler);
    }

    printf("Hello\n");
    return 0;
}
