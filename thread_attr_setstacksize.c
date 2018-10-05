
#include <pthread.h>  //for pthread_create,pthread_arttr_setstacksize
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   //for exit

//once thread is created after that it is called to this function

void *func(void *stack)
{
    printf("inside thread function\n");
    printf("set tack size=%d",*(int *)stack);
}
int main(int argc, char *argv[])
{
    int ret;
    size_t stacksize;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    //this function is used to get stack size 
     
    ret=pthread_attr_getstacksize (&attr, &stacksize);
    printf("Default stack size = %d\n",ret);
    stacksize=32767;

    //this function is used to set stack size
          
    ret=pthread_attr_setstacksize(&attr,stacksize);
    if(ret!=0)
    {
         printf("stack size is not set\n ");
         exit(1);
    }
         
    //for thread creation and calling function and passing argument of              stacksize
         
    pthread_create(&tid,&attr,func,&stacksize);

    //The pthread_join() function shall suspend execution of the calling            thread until the target thread terminates
    
    pthread_join(tid,NULL);
} 
