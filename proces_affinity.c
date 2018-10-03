
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   //for exit
#define __USE_GNU     //for CPU_SET,CPU_ZERO
#include <sched.h>    //for sched_set affinity
#include <unistd.h>   //for fork,ppid,pid

int main() 
{
    pid_t pid; 
    int ret,r;

    // We want to camp on the 2nd CPU. The ID of that core is #1.

    const int core_id = 1;

    //cpu_set_t: This data set is a bitset where each bit represents a CPU.

    cpu_set_t cpuset;

    //CPU_ZERO: This macro initializes the CPU set set to be the empty set.
   
    CPU_ZERO(&cpuset);

    //CPU_SET: This macro adds cpu to the CPU set set.
    
    CPU_SET(core_id, &cpuset);
      
    //creating process using fork

    r=fork();
    if(r<0)
    {
         perror("fork not created");
         exit(1);
    } 
             
    //sched_setaffinity: This function installs the cpusetsize bytes long af        finity mask pointed to by cpuset for the process or thread with the ID          pid.
     
    //parent process set scheduler

    if(r>0)
    {
         printf("iam in parent process pid=%d\n",getppid());
         ret = sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset);
    if (ret != 0) 
    {
         printf("sched_setaffinity is not set");
    }  
 
    //sched_getaffinity: This functions stores the CPU affinity mask for the        process or thread with the ID pid in the cpusetsize bytes long bitmap           pointed to by cpuset.

    ret = sched_getaffinity(pid, sizeof(cpu_set_t), &cpuset);
    if (ret != 0) 
    {
         printf("sched_getaffinity is not reciving");
    }
 
    }

    //CPU_ISSET: This macro returns a nonzero value (true) if cpu is a member       of the CPU set set, and zero (false) otherwise.

    //creaing child Process
 
    else if(r==0)
    {
         printf("iam in child process pid=%d\n",getpid()); 
    if (CPU_ISSET(core_id, &cpuset)) 
    {
         printf("Successfully set thread %d to affinity to CPU %d\n", pid,               core_id);
    }
    else 
    {
         printf("Failed to set thread %d to affinity to CPU %d\n", pid,                  core_id);
    }   
    }
    return 0;
}
