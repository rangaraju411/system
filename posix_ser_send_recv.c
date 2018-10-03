
#include <stdio.h>     //for printf and scanf 
#include <stdlib.h>    //for exit
#include <mqueue.h>    //for mq_open,mq_receive
#include <string.h>    //for strlen

#define SERVER_QUEUE_NAME   "/1.txt"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main ()
{
    mqd_t qd_server, qd_client;   // queue descriptors
    unsigned int i=1,t = 1;       // next token to be given to client

    printf ("Server: Hello, World!\n");
    char in_buffer [MSG_BUFFER_SIZE];
    char out_buffer [MSG_BUFFER_SIZE];
    struct mq_attr attr;

    //attributes for the message queue.

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    //The mq_open function is for opening a POSIX queue 

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY)) == -1) 
    {
         perror ("Server: mq_open (server)");
         exit (1);
    }

    while (1)
    {

    //mq_receive receives a message from the queue referred by the descriptor

    // get the oldest message with highest priority;
    if (mq_receive (qd_server, in_buffer, MSG_BUFFER_SIZE,&t) == -1)
    {
         perror ("Server: mq_receive");
         exit (1);
    }
    printf ("Server:id=%u\t,message received=%s\n",t,in_buffer);

    //send reply message to client

    if ((qd_client = mq_open (in_buffer, O_WRONLY)) == 1) 
    {
         perror ("Server: Not able to open client queue");
         //continue;
    }

    sprintf (out_buffer, "%s", "posix message queue");

    //mq_send send messaget to the client

    if (mq_send (qd_client, out_buffer, strlen (out_buffer) + 1,i) == -1) 
    {
         perror ("Server: Not able to send message to client");
         //continue;
    }  

    printf ("Server: response sent to client.\n");
    //t++;
    i++;
    }
}


