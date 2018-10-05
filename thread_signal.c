
#include <string.h>    //for strcpy
#include <pthread.h>   //for pthread_create,pthread_join
#include <stdio.h>     //for printf and scanf
#include <unistd.h>    //for sleep
#include <signal.h>    //for SIGSEGV

typedef struct data
{
    char name[30];
    int age;
}data;

void sig_func(int sig)
{
    printf("Caught signal:%d\n",sig);
    //signal(SIGSEGV,sig_func);
}

void func(data *p)
{
    printf("This is from thread function\n");
    signal(SIGSEGV,sig_func);
    strcpy(p->name,"welcome to epl");
    p->age=55;
    sleep(2);
}

int main()
{
    pthread_t tid;
    //pthread_attr_t attr;
    data *ptr,d;
    ptr=&d;

    //creating thread and passing structre pointer as argument of thread         function

    pthread_create(&tid,NULL,(void *)func,ptr);
    sleep(2);
    
    //send SIGSEGV signal to thread id using kill

    pthread_kill(tid,SIGSEGV);

    //waiting for termination of thread function

    pthread_join(tid,NULL);

    printf("Name:%s\n",ptr->name);
    printf("Age:%d\n",ptr->age);
}

