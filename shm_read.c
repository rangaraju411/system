
#include<stdio.h>      //for printf and scnaf
#include<stdlib.h>     //for exit
#include<sys/shm.h>    //for shmget,shmat,shmdt

#define size 1024

int main()
{
    int shmid1,shmid2;
    key_t key=0x30;
    char *ptr1,*ptr2;
    
    //creating shared memory using shmget and check created or not

    shmid1=shmget(key,size,IPC_CREAT|0666);
    shmid2=shmget(key,size,IPC_CREAT|0666);
    
    if(shmid1<0 | shmid2<0)
    {
         printf("shmid not creted");
         exit(1);
    }

    //attaching to shared memory segment and print the address
    
    ptr1=shmat(shmid1,NULL,0);
    printf("attached address=%p",ptr1);
    printf("reading  data from memory\n");
    printf("%s\n",ptr1);
   
    //detached to shared memory segment
    
    shmdt(ptr1);

    ptr2=shmat(shmid2,NULL,0);
    printf("attached address=%p",ptr2);
    printf("reding data from memory\n");
    printf("%s\n",ptr2);
  
    //detached to shared memory segment
    shmdt(ptr2);
}

