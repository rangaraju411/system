
connect posix_server.c

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
    char msg[]="/rangaraju"; //here "/ data" is mandatory otherwise mopen is fai                             led to open
    char in_buffer [MSG_BUFFER_SIZE];
    char temp_buf [10];
    struct mq_attr attr;

    //attributes for the message queue.

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_client = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) 
    {
         perror ("Client: mq_open (server)");
         exit (1);
    }

    while (t<5) 
    {

    // send message to server
        
    if (mq_send (qd_client, msg, strlen (msg) + 1,t++) == -1)  
    {
         perror ("Client: Not able to send message to server");
         //continue;
    }  

    // display token received from server
    printf ("Client: id=%d\n\n",t-1);

    }
    
    //The mq_close call closes the message queue descriptor.

    if (mq_close (qd_client) == -1) 
    {
         perror ("Client: mq_close");
         exit (1);
    }
     
    //mq_unlink removes the queue.

    /*if (mq_unlink (msg) == -1) 
    {
         perror ("Client: mq_unlink");
         exit (1);
    }*/       
    
    printf ("Client: bye\n");
    exit (0);
}
