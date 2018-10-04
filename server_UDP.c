  
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,bind
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen

#define PORT    8080 
#define MAXLINE 1024 

int main() 
{ 
    int sockfd,n,len;
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
    { 
         perror("socket creation failed"); 
         exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 

    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 

    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
         perror("bind failed"); 
         exit(EXIT_FAILURE); 
    } 
    
    printf("server receiving  data\n");
    
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
        MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);    
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    
    printf("server sending data\n");

    sendto(sockfd, "welcome to epl",15 ,MSG_CONFIRM,                                (const struct sockaddr     *) &cliaddr, len); 
    printf("Hello message sent.\n");  
      
    return 0; 
} 
