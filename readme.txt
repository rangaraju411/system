
Sys V message Queue:

 message queue is a linked list of messages stored within the kernel and identified by a message queue identifier. A new queue is created or an existing queue  opened by msgget().



posix message queue:

compilation steps
1.vim server.c
2.gcc server.c -o ser -lrt (without thread)
2.gcc server.c -o ser -lpthread -lrt (using thread)
3.communicate client and server need to give same SERVER_QUEUE_NAME "/1.txt"

if you want to execute messages in priority order we need to execute first client after execute server only
 

