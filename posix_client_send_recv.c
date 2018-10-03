
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
    unsigned int i;
    char msg[]="/welcome to epl";//here "/data" mandatory otherwise mopen is fai
    char in_buffer [MSG_BUFFER_SIZE];
    char temp_buf [10];
    struct mq_attr attr;
    
    //attributes for the message queue.
    
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    //The mq_open function is for opening a POSIX queue       

    if ((qd_client = mq_open (msg, O_RDONLY | O_CREAT,QUEUE_PERMISSIONS,&attr))     == -1) 
    {
         perror ("Client: mq_open (client)");
         exit (1);
    }

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) 
    {
         perror ("Client: mq_open (server)");
         exit (1);
    }
    
  
    // send message to server

    printf("client sending data to server\n");
    if (mq_send (qd_server, msg, strlen (msg) + 1,10) == -1) 
    {
         perror ("Client: Not able to send message to server");
         //  continue;
    }  
     
    // receive response from server

    printf("client receiving data from server\n");
    if (mq_receive (qd_client, in_buffer, MSG_BUFFER_SIZE,&i) == -1) 
    {
         perror ("Client: mq_receive");
         exit (1);
    }
  
    // display token received from server

    printf ("Client: id=%u,Token received from server: %s\n\n",i, in_buffer);
    
    //The mq_close call closes the message queue descriptor.
    
    if (mq_close (qd_client) == -1) 
    {
        perror ("Client: mq_close");
        exit (1);
    } 
    /*if (mq_unlink (msg) == -1) 
    {
         perror ("Client: mq_unlink");
         exit (1);
    }  */
    //printf ("Client: bye\n");

    return 0;
}
