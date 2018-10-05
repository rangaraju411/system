
#include <pthread.h>   //for pthread_create,pthread_arttr_setstacksize
#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit
#include <unistd.h>    //for sleep
#include <semaphore.h> //for sem_wait and sem_post

sem_t mutex;
 
void *thread(void* arg)
{
    //The sem_wait function atomically decreases the value of the semaphore      by 1
    
    sem_wait(&mutex);
    printf("\njust entered..\n");
	
    //critical section
    sleep(4);
	
    //signal
    printf("\nJust Exiting...\n");

    //The sem_post function atomically increases the value of the semaphore      by 1
    
    sem_post(&mutex);
}

/* void *mythread(void *arg)
{
    sem_wait(&mutex);
    printf("iam in thread2...\n");
    sleep(5);
    printf("\njust exiting..\n");
    //sem_post(&mutex) 
} 
  */                      
  
int main()
{
    int r;
    pthread_t t1,t2;

    //intialize semaphore

    sem_init(&mutex, 0, 1);
    
    //creating thread1 and checking it is created or not

    r=pthread_create(&t1,NULL,thread,NULL);
    if(r!=0)
    {
         printf("thread creation failed");
         exit(1);
    }
    
    //creating thread2

    pthread_create(&t2,NULL,thread,NULL);
   
    //checking thread1 function returns null or not

    r=pthread_join(t1,NULL);
    if(r!=0)
    {
         printf("thread joint is failed");
         exit(1);
    }

    pthread_join(t2,NULL);

    //destroying the semaphore

    sem_destroy(&mutex);
    printf("iam in main ");
    return 0;
}
