  
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <unistd.h>      //for close

#define PORT    8080 
#define MAXLINE 1024 
  
int main() 
{ 
    int sockfd; 
    int n, len;
    char buffer[MAXLINE]; 
    char *hello = "UDP Communication"; 
    struct sockaddr_in   servaddr; 
  
    // Creating socket file descriptor 

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
    { 
         perror("socket creation failed"); 
         exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    printf("client sending data\n");

    sendto(sockfd, (const char *)hello, strlen(hello), 
    MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
    sizeof(servaddr)); 
    printf("Hello message sent.\n"); 
          
    printf("client receiving data\n");

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
    MSG_WAITALL, (struct sockaddr *) &servaddr,&len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
} 

