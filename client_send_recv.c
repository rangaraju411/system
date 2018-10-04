
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,connect
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <unistd.h>      //for sleep
#include <arpa/inet.h>   //for inet_pton

#define PORT 8803

int main(int argc,char *argv[])
{
    struct sockaddr_in server;
    int sockfd,len,i;
    char str[100],data[100];
    
    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented)

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
         exit(1);
    }
    printf("sock=%d",sockfd);

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    //server.sin_addr.s_addr=atoi(argv[1]);

    //Convert IPv4 and IPv6 addresses from text to binary form 

    if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0) 
    {
         printf("\nInvalid address/ Address not supported \n");
         return -1;
    }

    //The connect() system call connects the socket referred to by the file         descriptor sockfd to the address specified by addr

    if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
    {
         printf("connection failed");
         exit(1);
    }
    
    //continously sending and receiving messages for server
   
    while(1)
    {
         printf("enter input[1/2/3]\n");
         //sleep(5);
         scanf("%d",&i);
         fflush(stdin);
    switch(i)
    {
         case 1:printf("enter data\n");
                fgets(str,100,stdin);
                sleep(5);
                send(sockfd,str,strlen(str),0);
                memset(str,0,sizeof(str));
                break;
         case 2:recv(sockfd,data,sizeof(data),0);
                printf("%s",data);
                memset(data,0,sizeof(data));
                 break;
         case 3:exit(1);
         default:printf("enter correct input");
    }
    }
 
    return 0;
}
