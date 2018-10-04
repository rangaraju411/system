
#include <stdio.h>   //for printf
#include <signal.h>  //for signal function
#include <unistd.h>  //for sleep

void sigtstp_handler(int signum)
{
    printf("signal num=%d",signum);
}

int main()
{
    signal(SIGTSTP,sigtstp_handler);//give input ctrl+z;
    sleep(5);
    printf("hello");
}

