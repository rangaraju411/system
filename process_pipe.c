
#include <stdio.h>     // for printf ,scanf etc
#include <string.h>    //for strlen function
#include <unistd.h>    //for fork,write,read,close
#include <stdlib.h>    //for exit

int main()
{
    int r,s,n,fd[2];
    char msg[]="welcome to EPL",buf[20];

    //Creating pipe, fd[0] is parent and fd[1] is child
	
    s=pipe(fd);
    if(s<0)
    {
         perror("pipe not created");
         exit(1);
    }

    //creating process using fork
     
    r=fork(); 
    if(r<0)
    {
	 printf("process not created");
         exit(1);
    }
     
    //parent process writing data into pipe
  
    if(r>0)
    {
	 printf("parent process writing data\n");
	 close(fd[0]);
	 //printf("enter data");
	 //fgets(msg,30,stdin);
         printf("parent pid=%d\n",getppid());
	 write(fd[1],msg,strlen(msg));       
	 close(fd[1]);
    }

    //child process reading data into pipe
    
    else if(r==0)
    {
	 printf("child process reading data\n");
	 close(fd[1]);
         printf("child pid=%d\n",getpid());
	 n=read(fd[0],buf,sizeof(msg));
	 //buf[n]='\0';
	 printf("%s\n",buf);
	 close(fd[0]);
    }
}

