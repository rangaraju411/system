
#include <pthread.h>  //for pthread_create,pthread_join
#include <stdio.h>    //for printf and scanf
#include <unistd.h>   //for sleep
#include <string.h>   //for strerror

pthread_t tid[2];
int counter;

void *t_handler(void *arg)
{
    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);
    sleep(5);
    for(i=0; i<(0xFFFFFFFF);i++);
    printf("\n Job %d finished\n", counter);
}

int main(void)
{
    int i = 0;
    int err;

    //creating threads using pthread_create

    while(i < 2)
    {
         err = pthread_create(&(tid[i]), NULL,t_handler, NULL);
         if (err != 0)
         printf("\ncan't create thread :[%s]", strerror(err));
         i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}
