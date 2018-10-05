
#include <stdlib.h>    //for exit
#include <unistd.h>    //for sleep
#include <stdio.h>     //for ptintf and scanf
#include <signal.h>    //for struct sigevent sev,sigprocmask
#include <time.h>      //struct itimerspec its

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN+1

void timer_thread(union sigval t)
{
    timer_t *tidp;
    int r;
    pthread_t tid;
    /* Note: calling printf() from a signal handler is not
    strictly correct, since printf() is not async-signal-safe;
    see signal(7) */

    puts("iam in signal handler\n");
    //pthread_create(&tid,NULL,thread_handler,NULL);
      
    r = timer_getoverrun(*tidp);
    if (r == -1)
         puts("timer_getoverrun");
    else
         printf("overrun count = %d\n", r);
    printf("Caught signal %d\n",SIG);
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its,i2;
    long long freq_nanosecs;
    sigset_t mask;
    struct sigaction sa;
    int i=0;
    double t,t1,t2;
  
    if (argc != 3) 
    {
         fprintf(stderr, "Usage: %s <sleep-secs> <freq-nanosecs>\n",argv[0]);
         exit(1);
    }

   /* Create the timer */

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_value.sival_ptr = &timerid;
    sev.sigev_notify_function=timer_thread;
    sev.sigev_notify_attributes=NULL;

    if (timer_create(CLOCKID, &sev, &timerid) == -1)
         printf("timer_create");
    printf("timer ID is 0x%lx\n", (long) timerid);
  
    printf("Sleeping for %d seconds\n", atoi(argv[1]));
    sleep(atoi(argv[1]));
    
    /* Start the timer */

    freq_nanosecs = atoll(argv[2]);
    its.it_value.tv_sec = freq_nanosecs / 1000000000;
    its.it_value.tv_nsec = freq_nanosecs % 1000000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;
    
    //set the timer

    if (timer_settime(timerid,0, &its, NULL) == -1)
         printf("timer_settime");

    /*Sleep for a while; meanwhile, the timer may expire
       multiple times */

    printf("Sleeping for %d seconds\n", atoi(argv[1]));
    sleep(atoi(argv[1]));
    
    return 0;
}

