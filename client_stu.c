
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,connect
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <arpa/inet.h>   //for inet_pton

#define PORT 8801

struct msg
{
    int id;
    char name[30];
    float sal;
};

int main(int argc,char *argv[])
{
    struct msg m;
    struct sockaddr_in server;
    int sockfd,len,i;
    char str[100],data[100];
   
    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented)

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
    }
    printf("sock=%d\n",sockfd);
  
    server.sin_family=AF_INET;//AF_INET (IPv4 protocol)
    server.sin_port=htons(PORT);//assign port numbe
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

    m.id=10;
    strcpy(m.name,"Hcl Technologies");
    //printf("enter emp sal\n");
    //scanf("%f",&m.sal);
    m.sal=12345;

    printf("client sending struct data\n");
    send(sockfd,&m,sizeof(m),0);
    //recv(sockfd,data,sizeof(data),0);

    return 0;
}
