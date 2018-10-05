   
#include <pthread.h>  //for pthread_create,pthread_arttr_setschedparam
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   //for exit

pthread_t thread1, thread2,thread3;
struct sched_param p1, p2;
pthread_attr_t attr1, attr2,attr3;
int policy; 

//when  thread1 is created after that this function is called
    
void *thread1_func (void *i)
{
    struct sched_param p3;
    int i1,i2;

    //check the scheduler set or not for thread1

    i1 = pthread_attr_getschedparam (&attr1, &p3);
    if(i1!=0)
    {
         printf("priority is not schedule t1\n");
    }
    printf ("in thread1 with priority :%u\n", p3.sched_priority);
} 

//when  thread2 is created after that this function is called

void *thread2_func (void *i)
{

    struct sched_param p3;

    int i1 = 0,p1,p2,ret;

    //receiving min and max priorites of FIFO scheduler

    p1 = sched_get_priority_max(SCHED_FIFO);
    p2 = sched_get_priority_min(SCHED_FIFO);

    //check the scheduler set or not for thread2

    i1= pthread_attr_getschedparam (&attr2, &p3);
    if(i1!=0)
    {
         printf("priority is not schedule\n");
    }  
    printf ("in thread2 with priority :%u\n",p3.sched_priority);
    printf("max=%d,min=%d\n",p1,p2);

}


//when  thread3 is created after that this function is called
  
void *thread3_func (void *i)
{

    struct sched_param p3;

    int i1 = 0;

    int policy;
    
    // check the scheduler set or not for thread3
  	
    i1 = pthread_getschedparam (thread3, (int *) &policy, &p3);
    //i1= pthread_attr_getschedparam (&attr2, &p3);
    printf ("in thread3 with priority :%u \n",p3.sched_priority);

}

int main ()  
{

    //struct sched_param p1, p2;

    //pthread_attr_t attr1, attr2;
    pthread_t pid;
    int r,ret,p=20;

    pthread_attr_init (&attr1);
    pthread_attr_init (&attr2);

    //setting scheduling polices,inherit scheduler and set scheduler parametr       values for thread1 

    ret=pthread_attr_setschedpolicy (&attr1,SCHED_FIFO);
    if(ret!=0)
    {
         printf("priority is not set\n");
    }  
    

    //inherit scheduler using thread attributes
  
    r=pthread_attr_setinheritsched (&attr1, PTHREAD_INHERIT_SCHED);
    if(r!=0)
    {
         printf("priority is not set\n");
    }   


    // set thread1 priority into  1

    p1.sched_priority = 1;
 
    //set scheduler parametrs for thread1

    ret= pthread_attr_setschedparam (&attr1, &p1);
    if(ret!=0)
    {
         printf("priority is not set\n");
    }
  
    //set thread1 scope

    pthread_attr_setscope(&attr1,PTHREAD_SCOPE_SYSTEM);
    ret= pthread_attr_getinheritsched(&attr1,&r);
    if(ret!=0)
    {
         printf("priority is not heritated\n");
    }

           
    //setting scheduling polices,inherit scheduler and set scheduler parametr    values for thread2 

         
    ret=pthread_attr_setschedpolicy (&attr2,SCHED_FIFO);
    if(ret!=0)
    {
         printf("priority is not set\n");
    }

    r=pthread_attr_setinheritsched (&attr2, PTHREAD_INHERIT_SCHED);
    if(r!=0)
    {
         printf("priority is not set");
    }


    //set thread2 priority into 99

    p2.sched_priority =99 ;   

    ret=pthread_attr_setschedparam(&attr2,&p2);
    if(ret!=0)
    {
         printf("priority is not set");
    }
    
    //set thread2 scope

    pthread_attr_setscope(&attr2,PTHREAD_SCOPE_SYSTEM);

    //checking scheduler is set or not for thread2

    ret= pthread_attr_getinheritsched(&attr2,&r);
    if(ret!=0)
    {
         printf("priority is not heritated");
    }
          
    //creating threads
           
    pthread_create (&thread1, &attr1, (void *) thread1_func, NULL);
    pthread_create (&thread2, &attr2, (void *) thread2_func, NULL);
    pthread_create (&thread3, NULL, (void *) thread3_func, NULL);
        
    //waiting for thread function termination

    pthread_join (thread1, NULL);
    pthread_join (thread2, NULL);
    pthread_join (thread3, NULL);

    //destroying the threads

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);
    //pthread_attr_destroy(&atr3);

    return 0;
}
