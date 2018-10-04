
#include <arpa/inet.h>   //for inet_ntoa 
#include <unistd.h>      //for get host name
#include <netdb.h>       //for struct hostent *hostinfo
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit

int main(int argc, char *argv[])
{
    char *host, **names, **addrs;
    struct hostent *hostinfo;

    if(argc == 1) 
    {
         char myname[256];
         gethostname(myname, 255);
         host = myname;
    }
    else
    host = argv[1];
    hostinfo = gethostbyname(host);

    if(!hostinfo) 
    {
         fprintf(stderr, "cannot get info for host: %s\n", host);
         exit(1);
    }

    //printf("results for host %s:\n", host);
    printf("Name: %s\n", hostinfo -> h_name);
    printf("Aliases:");
    names = hostinfo -> h_aliases;

    //receiving server ip address

    addrs = hostinfo -> h_addr_list;

    while(*addrs) 
    {
         printf(" %s", inet_ntoa(*(struct in_addr*)*addrs));
         addrs++;
    }
    printf("\n");

    return 0;
}
