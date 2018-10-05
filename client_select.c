
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,connect
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <arpa/inet.h>   //for inet_pton

#define PORT 8888

int main(int argc,char *argv[])
{
    struct sockaddr_in server;
    int sockfd,len;
    char str[]="select Client 1",buf[30];
 
    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented)
    
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
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

    recv(sockfd,buf,sizeof(buf),0);
    printf("rec data=%s\n",buf);
    printf("client sending data\n");
    send(sockfd,str,strlen(str),0);

    return 0;
}

