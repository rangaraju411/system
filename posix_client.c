
#include <string.h>    //for strlen
#include <stdio.h>     //for printf and scanf 
#include <stdlib.h>    //for exit
#include <mqueue.h>    //for mq_open,mq_receive

#define SERVER_QUEUE_NAME   "/1.txt"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main ()
{
    char client_queue_name [64];
    mqd_t qd_server, qd_client;   // queue descriptors
    unsigned int i=1,t=1;
    char msg[]="Welcome To Epl";
    char temp_buf [10];
    struct mq_attr attr;
    
    //attributes for the message queue.

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
   
    //The mq_open function is for opening a POSIX queue   
 
    if ((qd_client = mq_open (SERVER_QUEUE_NAME, O_WRONLY|O_CREAT,                  QUEUE_PERMISSIONS,&attr)) == -1) 
    {
         perror ("Client: mq_open (server)");
         exit (1);
    } 
    /*if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) 
    {
         perror ("Client: mq_open (server)");
         exit (1);
    }  */

    printf ("client is sending data\n");

    while (1) 
    {
    // send message to server

    if (mq_send (qd_client, msg, strlen (msg) + 1,t++) == -1)  
    {
         perror ("Client: Not able to send message to server");
         exit(EXIT_FAILURE);
    }  
    printf("sending id=%u\n",t-1);
    if(t>10)
    break;
    }       
    
    printf ("Client: bye\n");
    
    return 0;
}
