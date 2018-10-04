
#include<stdio.h>      //for printf and scanf
#include<stdlib.h>     //for exit
#include<sys/shm.h>    //for shmget,shmat,shmdt

#define size 1024

int main()
{
    int shmid;
    key_t key=0x30;
    char *ptr;
    
    //creating shraedmemory using shmget and check creted or not

    shmid=shmget(key,size,IPC_CREAT|0666);
    if(shmid<0)
    {
         printf("shmid not creted");
         exit(EXIT_FAILURE);
    }
   
    //attaching to shared memory segment and print the address

    ptr=shmat(shmid,NULL,0);
    printf("attached address=%p ",ptr);
    printf("writing data into memory:");
    scanf("%s",ptr);
    //gets(ptr);
    printf("%s",ptr);
  
    //detached to shared memory segment
    
    shmdt(ptr);

    //detaching and removing shared memory segment
   
    //shmctl(shmid,IPC_RMID,0);
}
