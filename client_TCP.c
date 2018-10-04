
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,connect
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <arpa/inet.h>   //for inet_pton

#define PORT 7986

int main(int argc,char *argv[])
{
    struct sockaddr_in server;
    int sockfd1,len;
    char str[]="welcome to EPL",buf[30];

    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented)

    if((sockfd1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
    }
    printf("sock=%d\n",sockfd1);

    server.sin_family=AF_INET;//AF_INET (IPv4 protocol)
    server.sin_port=htons(PORT);//assign port number
    //server.sin_addr.s_addr=atoi(argv[1]);
     
    //Convert IPv4 and IPv6 addresses from text to binary form 

    if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0) 
    {
         printf("\nInvalid address/ Address not supported \n");
         return -1;
    } 

    //The connect() system call connects the socket referred to by the file         descriptor sockfd to the address specified by addr

    if(connect(sockfd1,(struct sockaddr*)&server,sizeof(server))<0)
    {
         printf("connection failed");
         exit(1);
    }

    printf("client receiving data\n");
    recv(sockfd1,buf,sizeof(buf),0);
    printf("recv data=%s\n",buf);

    printf("client sending data\n");
    send(sockfd1,str,strlen(str),0);

    return 0;
}
