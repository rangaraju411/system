
#include <stdio.h>     //for printf and scanf
#include <time.h>      // for clock_t t,clock()
#include <stdlib.h>    //for exit
#include <unistd.h>    //for fork

int main()
{
    int r;
    double time_taken;
    clock_t t;
    t = clock();
  
    //create process using fork and check creted or not
    r=fork();
    if(r<0)
    {
         printf("process is not created");
         exit(1);
    }

    //executing parent process

    if(r)
    {
         printf("iam in parent process\n");
         printf("parent process id=%d\n",getppid());
    }

    //executing child process

    else
    {
         printf("iam in child process\n");
         printf("iam in child process id=%d\n",getpid());
    }

    //calculate execution time of process

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("time taken =%lf\n",time_taken);
    
    return 0;
}


