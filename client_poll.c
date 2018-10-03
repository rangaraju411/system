
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,connect
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <arpa/inet.h>   //for inet_pton


#define PORT 8888
//struct sockaddr_in server;

int main(int argc,char *argv[])
{
    struct sockaddr_in server;
    int sockfd[10],len,i=0,j=0;
    char *str[]={"Hi","Hello","HCL","welcome to EPL","Embedded Systems"};
    char buf[30];

    for(i=0,j=0;i<10 && j<5;i++,j++)
    {

    //creating socket and check it is created or not   
    //SOCK_STREAM: TCP(reliable, connection oriented

    if((sockfd[i]=socket(AF_INET,SOCK_STREAM,0))<0)
    {
         printf("socket is not created");
         exit(1);
    }

    printf("sock=%d",sockfd[i]);
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT+i);
    //server.sin_addr.s_addr=atoi(argv[1]);
    
    //Convert IPv4 and IPv6 addresses from text to binary form 

    if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0) 
    {
         printf("\nInvalid address/ Address not supported \n");
         return -1;
    }
  
    //The connect() system call connects the socket referred to by the file         descriptor sockfd to the address specified by addr

    if(connect(sockfd[i],(struct sockaddr*)&server,sizeof(server))<0)
    {
         printf("connection failed");
         exit(1);
    }

    printf("client receiving data\n");
    recv(sockfd[i],buf,sizeof(buf),0);
    printf("rec data=%s\n",buf);
    printf("client sending data\n");
    send(sockfd[i],str[j],strlen(str[j]),0);
    }//end for loop
    
    return 0;
}
