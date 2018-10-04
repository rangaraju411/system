#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,connect
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <unistd.h>      //for fork
#include <arpa/inet.h>   //for inet_pton

#define PORT 7900

int main(int argc,char *argv[])
{
    struct sockaddr_in server;
    int sockfd1,len,ret;
    char str[]="welcome to HCL",buf[100];
    
    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented

    if((sockfd1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
         exit(1);
    }
    printf("sock=%d",sockfd1);

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    //server.sin_addr.s_addr=atoi(argv[1]);

    //Convert IPv4 and IPv6 addresses from text to binary form 

    if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0) 
    {
         printf("\nInvalid address/ Address not supported \n");
         return -1;
    }

    //creating process using fork system

    ret=fork();
    if(ret<0)
    {
         perror("process is not created");
         exit(1);
    }
    
    //parent process connects to adresss specified by server addresss

    if(ret>0)
    {
         printf("parent connect to the server\n");
    if(connect(sockfd1,(struct sockaddr*)&server,sizeof(server))<0)
    {
         printf("connection failed");
         exit(1);
    }     
    }
 
    //child process sending and receiving data from server

    else if (ret==0)
    {
         printf("client receiving  data\n");
         recv(sockfd1,buf,sizeof(buf),0);
         printf("recv data=%s\n",buf);

         printf("client sending data\n");
         send(sockfd1,str,strlen(str),0);
         memset(buf,0,sizeof(buf));

         printf("client recv data\n");
         recv(sockfd1,buf,sizeof(buf),0);
         printf("rec data=%s\n",buf);
    }

    return 0;
}
