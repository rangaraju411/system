
#include <stdio.h>       //for printf and scanf
#include <stdlib.h>      //for exit
#include <sys/socket.h>  //for socket,bind,listen,accept
#include <netinet/in.h>  //for struct sockaddr_in server
#include <string.h>      //for strlen
#include <unistd.h>      //for fork

#define PORT 7987 

int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c,ret,status;
    struct sockaddr_in server , client;
    char *message , client_message[2000];
    pthread_t thread_id;
    
    //Create socket and check it is created or not

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
         printf("Could not create socket");
         exit(EXIT_FAILURE);
    }
    printf("Socket des=%d",socket_desc);
     
    //Prepare the sockaddr_in structure

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT );
     
    //bind function binds the socket to the address and port number                 specified in addr.

    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
         //print the error message
         perror("bind failed. Error");
         return 1;
    }
    puts("bind done");
     
    //it waits for the client to approach the server to make a connection
    
    listen(socket_desc , 3);   
     
    //Accept and incoming connection

    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	
    while(1)
    {
         int *ptr=(int *)malloc(sizeof(int));
         client_sock=*(int *)ptr;
         //printf("socket=%d\n",client_sock);

         //At this point, connection is established between client and server            and they are ready to transfer data.

         client_sock = accept(socket_desc, (struct sockaddr *)&client,
         (socklen_t*)&c);
         puts("Connection accepted");
     
         //creating process using fork

         ret=fork();
    if(ret<0)
    {
         printf("process not created");
         exit(1);
    }

    if(ret>0)
    {
         printf("iam in parent process pid=%d\n",getppid());
         printf("write data into client\n");
         message = "Greetings! Hello\n";
         send(client_sock , message , strlen(message),0);

    }

    else 
    {
         int read_size;   
         printf("i am in child process pid=%d\n",getpid());
         printf("receiving data from client\n");
         recv(client_sock , client_message , 2000 , 0);
         printf("recv data=%s\n",client_message);
         send(client_sock , client_message , strlen(client_message),0);
		
         //clear the message buffer

	 memset(client_message, 0, 2000);
    }
    }
    
    return 0;
}

