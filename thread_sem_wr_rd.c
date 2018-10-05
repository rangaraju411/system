
#include <pthread.h>   //for pthread_create,pthread_arttr_setstacksize
#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit
#include <semaphore.h> //for sem_init,sem_post

sem_t sid;
char str[100];

//writing data thread1 into buffer

void *mythread(void *arg)
{
    int i=0;
  
    //The sem_post function atomically increases the value of the semaphore      by 1
    
    sem_post(&sid);
    printf("thread1 write data\n");
    printf("enter data\n");
    fgets(str,100,stdin);

    //The sem_wait function atomically decreases the value of the semaphore      by 1

    sem_wait(&sid);
    printf("exit into sem\n");
}

//reading data thread2 from buffer

void *mythread1(void *a)
{
    sem_post(&sid);
    printf("thread2 reading data\n");
    printf("reading data=%s",str);
    sem_wait(&sid);
    printf("exit into sem\n");

}

int main()
{
    //sem_t sid;
    int r;
    pthread_t tid,tid1;

    //for initializing semaphore

    sem_init(&sid,0,0);
  
    //creating thread

    r=pthread_create(&tid,0,mythread,NULL);
    if(r!=0)
    {
         printf("thread creation is failed");
         exit(1);
    }
    pthread_join(tid,NULL);

    pthread_create(&tid1,0,mythread1,NULL);
    pthread_join(tid1,NULL);
   
    //destroying semaphore

    sem_destroy(&sid);
}

