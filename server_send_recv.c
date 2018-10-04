
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,bind,listen,accept
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <unistd.h>      //for sleep

#define PORT 8803

int main(int argc,char *argv[])
{
    int i;
    //char ch;
    struct sockaddr_in server;
    int sockfd,newsock,l;
    char data[100],str[100];
    
    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented)
  
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
    }
    printf("sock=%d",sockfd);

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=INADDR_ANY;

    //bind function binds the socket to the address and port number                   specified in addr.

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
    
    //continuosloy sending and receiving messages for client

    while(1)
    {
         printf("enter input[1/2/3]\n");
         //sleep(5);
         scanf("%d",&i);
         fflush(stdin);
    switch(i)
    {
         case 1: printf("enter data\n");
                 fgets(str,100,stdin);
                 sleep(5);
                 send(newsock,str,strlen(str),0);
                 memset(str,0,sizeof(str));
                 break;
         case 2:recv(newsock,data,sizeof(data),0);
                printf("%s",data);
                memset(data,0,sizeof(data));
                break;
         case 3:exit(1);

         default:printf("enter correct input");
    }
    }
    
    return 0;
}


