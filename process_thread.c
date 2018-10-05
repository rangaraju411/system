
#include<stdio.h>   //for printf ,scanf etc
#include<string.h>  //for strlen function
#include<unistd.h>  //for fork,getpid,getppid
#include<stdlib.h>  //for exit
#include<pthread.h> //for phtread_create,pthread_join
#include<sys/wait.h>//for wait function

//once thread is created after that it is called to this function

void *fun(void *i)
{ 
    printf("iam in thread fun\n");
    printf("pid=%d\n",*(int *)i);
}

int main()
{
    int r,s,n;
    char msg[]="welcome to EPL",buf[20];
    pthread_t tid;

    //fork is used to create process

    r=fork();
    if(r<0)
    {
	 printf("process not created");
         exit(1);
    }

    //parent process waiting until termination of child process
	
    if(r>0)
    {
         printf("parent is waiting state\n");
         printf("parent pid=%d\n",getppid());
         s=getppid();
         wait(&n);
         printf("end of parent process\n");
         //pthread_create(&tid,NULL,fun,(void *)&s);
         //pthread_join(tid,NULL);
    }

    //child process is creating thread and pass child pid as argument

    else if (r==0)
    {
	 printf("child process creating thread\n");
         printf("child pid=%d\n",getpid());
         s=getpid();
         pthread_create(&tid,NULL,fun,(void *)&s);
         pthread_join(tid,NULL);

    }
}
