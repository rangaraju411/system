
#include <stdio.h>   //for printf
#include <signal.h>  //for signal function
#include <unistd.h>  //for sleep

//it will raise perform invalid operation like divided by zero

void sigfpe_handler(int signum)
{
    printf("signal num=%d\n",signum);
}

int main()
{
    int n;
    
   // signal handler with signal number SIGFPE
   
    signal(SIGFPE,sigfpe_handler);
    printf("enter n value");
    scanf("%d",&n);
    n=n/0;
    printf("hello");
}


