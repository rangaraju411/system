
#include <stdio.h>    //for printf and scanf	
#include <stdlib.h>   //for exit
#define __USE_GNU     //for cpu_set,cpu_zero
#include <pthread.h>  //for pthread_create
  
struct thread_info 
{ 
    pthread_t thread_id; // ID returned by pthread_create()
    int core_id; // Core ID we want this pthread to set its affinity to
};
 
void * thread_camper(void *arg) 
{
    int ret;
    struct thread_info *thread_info = arg;
    char *buffer;
    //const pthread_t pid = pthread_self();
    const pthread_t pid = thread_info->thread_id;
    const int core_id = thread_info->core_id;

    //cpu_set_t: This data set is a bitset where each bit represents a CPU
  
    cpu_set_t cpuset;

    //CPU_ZERO: This macro initializes the CPU set set to be the empty set

    CPU_ZERO(&cpuset);

    //CPU_SET: This macro adds cpu to the CPU set set.
 
    CPU_SET(core_id, &cpuset);

    //pthread_setaffinity_np: The pthread_setaffinity_np() function sets the     CPU affinity mask of the thread.

    ret =pthread_setaffinity_np(pid, sizeof(cpu_set_t), &cpuset);
    if (ret != 0) 
    {
         printf("pthread_setaffinity_np");
    } 
   
    //pthread_getaffinity_np: The pthread_getaffinity_np() function returns      the CPU affinity mask of the thread thread in the buffer pointed to by       cpuset
 
    ret =pthread_getaffinity_np(pid, sizeof(cpu_set_t), &cpuset);
    if (ret != 0) 
    {
         printf("pthread_getaffinity_np");
    }
 

    //CPU_ISSET: This macro returns a nonzero value (true) if cpu is a member       of the CPU set set, and zero (false) otherwise.


    if (CPU_ISSET(core_id, &cpuset)) 
    {
         printf( "Successfully set thread %lu to affinity to CPU %d\n",pid,              core_id);
    } 
    else 
    {
         printf("Not set thread %lu to affinity to CPU %d\n",pid,core_id);
         exit(1); 
    } 
}
 
int main(int argc, char *argv[]) 
{
 
    //Initialize thread creation attributes
    pthread_attr_t attr;
    int tnum,ret;
    const int num_threads = 4;
    const int attr_init_result = pthread_attr_init(&attr);
 
    if (attr_init_result != 0) 
    {
         printf("pthread_attr_init");
    }
 
    //We will set the stack size limit to is 1 MB (0x100000 bytes)


    const int stack_size = 0x100000;
    const int setstacksize_result = pthread_attr_setstacksize(&attr,                stack_size);
    if (setstacksize_result != 0) 
    {
         printf("pthread_attr_setstacksize");
    }
 
    //Allocate memory for pthread_create() arguments
 

    struct thread_info *thread_info = calloc(num_threads, 
                                      sizeof(struct thread_info));
    if (thread_info == NULL) 
    {
         printf("not allocate calloc");
    }
 
 
    for (tnum = 0; tnum < num_threads; tnum++) 
    {
 
         thread_info[tnum].core_id = tnum;
    
         //The pthread_create() call stores the thread ID into corresponding             element of thread_info[]

         ret =pthread_create(&thread_info[tnum].thread_id, &attr,                           &thread_camper,&thread_info[tnum]);
    if(ret!= 0) 
    {
         printf("pthread_is not create");
         exit(1);
    }
    pthread_join(thread_info[tnum].thread_id,NULL);
    }
 
    //Destroy the thread attributes object, since it is no longer needed

    ret =  pthread_attr_destroy(&attr);
    if (ret != 0) 
    {
         printf("pthread_attr_destroy");
    }
 
    free(thread_info);
    return 0;
}
