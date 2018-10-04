
#include <pthread.h>      //for pthread_create
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,connect
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <arpa/inet.h>   //for inet_pton

#define PORT 7987

void *client_handler(void *sockfd);

int main(int argc,char *argv[])
{
    struct sockaddr_in server;
    int sockfd1,len;
    pthread_t tid;
    char str[]="welcome to HCL",buf[1000];

    //Create socket and check it is created or not

    if((sockfd1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
         exit(1);
    } 
    printf("sock=%d\n",sockfd1);

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

    if(connect(sockfd1,(struct sockaddr*)&server,sizeof(server))<0)
    {
         printf("connection failed");
         exit(1);
    }
    
    //creating thread and passing sockfd as argument of thread function

    pthread_create(&tid,NULL,client_handler,(void *)&sockfd1);
    pthread_join(tid,NULL);

    puts("Handler assigned");
    } 

void *client_handler(void *sockfd1)
{
    int s;
    struct sockaddr_in server;
    char str[]="welcome to HCL",buf[100];
    s=*(int *)sockfd1;
     
    printf("iam in thread function\n");
    printf("sock=%d\n",s);
    printf("client receiving data\n");
    recv(s,buf,sizeof(buf),0);
    printf("recv data=%s\n",buf);

    printf("client sending data\n");
    send(s,str,strlen(str),0);
    memset(buf,0,sizeof(buf));
    
    printf("client receiving data\n");
    recv(s,buf,sizeof(buf),0);
    printf("recv data=%s\n",buf);
    //memset(buf,0,sizeof(buf));

}
