
#include <unistd.h>   //for fork,execvp
#include <stdlib.h>   //for exit
#include <stdio.h>    //for printf and scanf
#include <sys/wait.h> //for wait

int main()
{
    //arguments for ls, will run: ls  -l /bin                                
    char * ls_args[3] = { "ls", "-l", NULL} ;
    pid_t c_pid, pid;
    int status;
    
    //creating process using fork and check it is created or not

    c_pid = fork();
    if(c_pid<0)
    {
         perror("process not created");
         exit(1);  
    }

    //child process executing ls using execvp system call

    if (c_pid == 0)
    {
         printf("child pid=%d\n",getpid());
         printf("Child: executing ls\n");
         execvp( ls_args[0], ls_args);
         perror("execve failed");
    }     
  
    //parent process is waiting for termination status of child process

    else if (c_pid > 0)
    {
    if( (pid = wait(&status)) < 0)
    {
         perror("wait");
         exit(1);
    }
    printf("parent pid=%d\n",getppid());
    printf("Parent: finished\n");

    }  
    
    return 0; 
}
