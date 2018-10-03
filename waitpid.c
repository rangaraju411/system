
#include <sys/wait.h> //for waitpid and wifexited
#include <stdlib.h>   //for exit
#include <unistd.h>   //for fork
#include <stdio.h>    //for printf and scanf


int main()
{
    pid_t cpid, w; 
    int status;
    
    //create process using fork
                  
    cpid = fork();
    if (cpid == -1) 
    { 
         perror("fork"); 
         exit(EXIT_FAILURE); 
    }

    //executing  child process
        
    if (cpid == 0) 
    {            
         printf("Child PID is %ld\n", (long) getpid());
    }

    //parent process is waiting for exit status of child process
    
    else 
    {
         printf("Parent PID is %ld\n", (long) getppid());                  
         w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
    if (w == -1) 
    {
         perror("waitpid"); 
         exit(EXIT_FAILURE); 
    } 

    if (WIFEXITED(status)) 
    {
         printf("exited, status=%d\n", WEXITSTATUS(status));
    }  
    }
}


