
#include <fcntl.h>      //for write
#include <string.h>     //for strlen
#include <unistd.h>     //for write,close and sleep
#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit
#include <sys/sem.h>   //for semget and semop

void take_sem(void);
void critical_sem(void);
void rel_sem(void);
struct sembuf semb;

int semid,nsem=1,fd1;

int main()
{
    key_t key=0x30;
    int nsem=1;
        
    //creating named pipe with readonly mode
    
    fd1=open("myfifo3",O_RDONLY);
    
    //for creating semaphore using semget and check it is created or not

    semid=semget(key,nsem,IPC_CREAT|0666);
    if(semid<0)
    {
         printf("sem is not created");
         exit(EXIT_FAILURE);
    }
 
    take_sem();
    critical_sem();
    rel_sem();
}
void take_sem()
{
    int v;
    struct sembuf semb;
    printf("p4 taken semaphore\n");

    semb.sem_num=0;
    semb.sem_op=-1;//taken semaphore
    semb.sem_flg=SEM_UNDO;
    
    //semop is used for changing the value of the semaphore:
   
    if(semop(semid,&semb,nsem)==-1)
    {
         printf("semaphore failed");
         exit(1);
    }

    //semctl function allows direct control of semaphore information

    v=semctl(semid,0,GETVAL);
    printf("semval=%d",v);
}
void critical_sem()
{
    //int fd1;
    char buf[100];
    //fd1=open("myfifo3",O_RDONLY);
    
    //checking pipe is created or not

    if(fd1<0)
    {
         printf("pipe not created");
         exit(1);
    }
    sleep(10);
    printf("reading data into pipe\n");
    read(fd1,buf,sizeof(buf));
    printf("%s\n",buf);

    close(fd1);
}
void rel_sem()
{
    int v;
    struct sembuf semb;
    printf("p4 release semaphore\n");

    semb.sem_num=0;
    semb.sem_op=1;//releasing semaphore
    semb.sem_flg=SEM_UNDO;

    if(semop(semid,&semb,nsem)==-1)
    {
         printf("semaphore failed");
         exit(1);
    }

    v=semctl(semid,0,GETVAL);
    printf("semval=%d",v);
}
