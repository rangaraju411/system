
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,bind,listen,accept
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen

#define PORT 8801

struct msg1
{
    int id;
    char name[30];
    float sal;
};

int main(int argc,char *argv[])
{
    int i;
    //char ch;
    struct sockaddr_in server;
    struct msg1 m1;
    int sockfd,newsock,l;
    char data[100],str[100];
    
    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented)

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
         exit(1);
    }
    printf("sock=%d\n",sockfd);

    server.sin_family=AF_INET;//AF_INET (IPv4 protocol)
    server.sin_port=htons(PORT);//assign port number
    server.sin_addr.s_addr=INADDR_ANY;//INADDR_ANY to specify the IP address

    //bind function binds the socket to the address and port number                 specifid in addr.

    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
    {
         printf("bind to address failed");
         exit(1);
    }

    //listen waits for the client to approach the server to make connection

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
    
    printf("server receiving struct data\n");
    recv(newsock,&m1,sizeof(m1),0);
    printf("name=%s,id=%d,sal=%f\n",m1.name,m1.id,m1.sal);
    return 0;
}


