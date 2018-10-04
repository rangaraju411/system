
#include <stdio.h>   //for printf
#include <signal.h>  //for signal function
#include <unistd.h>  //for sleep

void display_message(int s) 
{
    printf("sig alarm=%d\n",s );
}

int main(void) 
{
    int n=10;
   
    //The SIGALRM signal is raised when a time interval specified in a call to      the alarm or alarmd function expires.

    signal(SIGALRM, display_message);
    alarm(3);
    pause();
    printf("%d\n",n);
}
