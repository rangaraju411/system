
#include <stdio.h>   //for printf
#include <signal.h>  //for signal function
#include <unistd.h>  //for sleep

//it will raise try to access inactive memory

void sigsegv_handler(int signum)
{
    printf("signal num=%d\n",signum);
}

int main()
{
    int n;
    
    signal(SIGSEGV,sigsegv_handler);
    printf("enter n value");
    scanf("%d",n);
    printf("hello");
}

