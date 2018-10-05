
#include <string.h>   //for strerror
#include <pthread.h>  //for pthread_create,pthread_arttr_setstacksize
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   //for exit
 
pthread_t tid[2];
int counter;
pthread_mutex_t lock;
 
void* threadFun(void *arg)
{	
    //acquire the lock
      
    pthread_mutex_lock(&lock);

    // Mutex is locked and no other thread can use this function 
    // until it is unlocked 

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d has started\n", counter);
    for(i=0; i<(0xFFFFFFFF);i++);
    printf("\n Job %d has finished\n", counter);
   
    //release lock
   
    pthread_mutex_unlock(&lock);		
    return NULL;
}
 
int main()
{
    int i = 0;
    int error;
      
    //initializing the thread mutex

    if(pthread_mutex_init(&lock,NULL)!=0)
    {
         printf("\n mutex init has failed\n");
	 return 1;
    }

    //creating threads using pthread_create

    while(i < 2)
    {
         error = pthread_create(&(tid[i]), NULL, &threadFun, NULL);
         if (error != 0)
	 printf("\nThread can't be created : [%s]", strerror(error));
	 i++;
    }
    
    // waitng for thread function termination
		     
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
 
    //destroy the thread mutex

    pthread_mutex_destroy(&lock);
	     
    return 0;
}
