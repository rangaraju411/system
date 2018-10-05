
#include<unistd.h>     //for sleep
#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit
#include <sys/sem.h>   //for semget and semctl


void take_sem(void);
void critical_sem(void);
void rel_sem(void);
//struct sembuf semb;
int semid,nsem=1;

int main()
{
    int v;
    key_t key=0x30;
    //int nsem=1;
    
    //creating semaphore using semget and check created or not

    semid=semget(key,nsem,IPC_CREAT|0666);
    if(semid<0)
    {
         printf("sem is not created");
         exit(1);
    }
    v=semctl(semid,0,GETVAL);
    printf("semval=%d",v);
    take_sem();
    critical_sem();
    rel_sem();
}

void take_sem()
{
    struct sembuf semb;
    int v;
    printf("p1 taken semaphore\n");
    semb.sem_num = 0;
    semb.sem_op  = -1;//taken semaphore
    semb.sem_flg = SEM_UNDO |IPC_NOWAIT;//no wait for resources
 
    if(semop(semid,&semb,nsem)==-1)
    printf("semaphore is taken");
    v=semctl(semid,0,GETVAL);
    //semctl(semid,0,SETVAL,1);
    printf("semval=%d",v);
}

void critical_sem()
{
    int i;
    sleep(10);
    for(i=0;i<10;i++)
    {
         printf("%d\n",i);
         //sleep(2);
    }
}

void rel_sem()
{
    int v;
    struct sembuf semb;
    printf("p1 releasing semaphore\n");
    semb.sem_num = 0;
    semb.sem_op  = 1;//releasing semaphore
    semb.sem_flg = SEM_UNDO;

    //semop is used for changing the value of the semaphore:

    if(semop(semid,&semb,nsem)==-1)
    printf("semaphore failed");
    
    //semctl function allows direct control of semaphore information
    v=semctl(semid,0,GETVAL);
    printf("sem val=%d",v);
}
