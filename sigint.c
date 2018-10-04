
#include <stdio.h>   //for printf
#include <signal.h>  //for signal function
#include <unistd.h>  //for sleep

//it is called when siganl function raise the SIGINT siganl

void sigint_handler(int signum)
{
    printf("signal num=%d\n",signum);
}

int main()
{
    signal(SIGINT,sigint_handler);//give input ctri+c;
    sleep(5);
    printf("hello\n");
}
