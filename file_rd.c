
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   // for exit
#include <fcntl.h>    // for fopen,fprintf

int main()
{
    FILE *fp;
    char ch,str[200];
    int c=0,n=0;

    //Here fopen is used to opening the file with read mode
 
    fp=fopen("file_wr.c","r");
    if(fp==NULL)
    {
         printf("file is not created");
         exit(1);
    }
    
    //reading data  until end of the file data

    while((ch=(fgetc(fp)))!=EOF)
    {
         if(ch==' ')
         c++;
         if(ch=='\n')
         n++;
         printf("%c",ch);
         ch++;
    }  
    
    printf("no of spaces in file=%d\n",c);
    printf("no of lines=%d\n",n);
    fclose(fp);

    return 0;
}
