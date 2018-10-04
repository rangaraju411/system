 
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,bind,listen,accept
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen

#define  PORT 7986

int main(int argc,char *argv[])
{
    int i;
    //char ch;
    struct sockaddr_in server;
    int sockfd,newsock,l;
    char data[100],str[100]="welcome to hcl";
    
    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented)

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
         exit(EXIT_FAILURE);
    }
    printf("sock=%d\n",sockfd);

    server.sin_family=AF_INET;//AF_INET (IPv4 protocol)
    server.sin_port=htons(PORT);//assign port number
    server.sin_addr.s_addr=INADDR_ANY;//INADDR_ANY to specify the IP address

    //bind function binds the socket to the address and port number                 specified in addr.
 
    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
    {
         printf("bind to address failed");
         exit(1);
    }
  
    //it waits for the client to approach the server to make a connection.
 
    if((listen(sockfd,3))<0)
    {
         perror("listen failed");
         exit(1);
    }
 
    l=sizeof(server);

    //At this point, connection is established between client and server,           and  they are ready to transfer data.

    if((newsock=accept(sockfd,(struct sockaddr*)&server,&l))<0)
    {
         perror("accept is failed");
         exit(1);
    }

    printf("server sending  data\n");
    send(newsock,str,strlen(str),0);

    printf("server receiving data\n");
    recv(newsock,data,sizeof(data),0);
    printf("recv data=%s",data);
  
    return 0;
}


