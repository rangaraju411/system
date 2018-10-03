
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   // for exit
#include <fcntl.h>    // for fopen,fprintf

int main()
{
    FILE *fp;

    //Here fopen is used to opening the file with write mode
    
    fp=fopen("1.txt","w");
    
    if(fp<0)
    {
         printf("file is not created");
         exit(1);
    }
     
    //fprintf write  data into  1.txt file
    fprintf(fp,"Hcl Technologies",16);
    fclose(fp);
}
