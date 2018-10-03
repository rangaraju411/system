
#include <stdio.h>       //for printf and scanf
#include <unistd.h>      //for write,read
#include <fcntl.h>       //for fcntl,open
#include <string.h>      //for strlen
#include <stdlib.h>      //for exit

//create pipe using this command-mkfifo pipename(myfifo1)
//remove pipe using this command-rm pipename(myfifo1)

int main()
{
    int fd1,fd2,i=0;
    char buf[100],data[100];

    //Here I am creating two fifos one for reading and another one is writing
     
    fd1=open("myfifo1",O_RDONLY);
    fd2=open("myfifo2",O_WRONLY);

    if(fd1<0 || fd2<0)
    {
         printf("pipe not created");
         exit(1);
    }
  
    //F_SETFL: Set the file status flags to the value specified by arg. File        access mode here in our purpose use only for O_NONBLOCK flag.

    if(fcntl(fd1,F_SETFL,O_NONBLOCK)<0)
         exit(1);

    //reading and writing operatons perfomed using write and read system calls

    while(1)
    {
         read(fd1,buf,sizeof(buf));
         printf("%s",buf);
         printf("enter data:");
         fgets(data,100,stdin);
         write(fd2,data,strlen(data)+1);
         memset(data,0,sizeof(data));
         i++;
         //if(i>3)
         //break;
    }
 
    //closing file descriptors

    close(fd1);
    close(fd2);
}
