
//popen() allows you to run a command and capture the output of it

#include <stdio.h>     //for printf and scanf
#include <stdlib.h>    //for exit 

int main(void)
{ 
    char buf[1024];
    FILE *in;
    int status;    
                      
    //creating a process using popen first argument need to give shell comma        nd
    in = popen("ps -al", "r");
      
    if(in == NULL)
    {
         perror("popen:");
	 exit(EXIT_FAILURE);
    }

    // Write the output of the command to the console.
   
    while(fgets(buf, sizeof(buf), in) != NULL)
    {
	 printf("%s", buf);
    }

    status=pclose(in);
    if(status==-1)
    {
         perror("pclose:");
         exit(1);
    }

    return 0;
}
	
