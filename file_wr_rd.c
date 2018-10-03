
#include <stdio.h>    //for printf and scanf
#include <stdlib.h>   // for exit
#include <fcntl.h>    // for fopen,fprintf

int main()
{
    FILE *fp;
    char ch,str[100],t;
    int i=0,j,l=0;

    //Here fopen is used to opening the file with write and read mode

    fp=fopen("1.txt","r+");
    if(fp==NULL)
    {
         printf("file not opened");
         exit(1);
    } 

    //reading data from file and again write  data into the same file using         fprintf


    while((ch=(fgetc(fp)))!=EOF)
    {
         str[i++]=ch;
         ch++;
         l++;
    } 
    str[i]='\0';
    printf("%s",str);
    printf("len=%d",l);
 
    //set file descriptor into starting position

    fseek(fp,0,SEEK_SET);

    for(j=0;j<l/2;j++)
    {
         t=str[j];
         str[j]=str[l-j-1];
         str[l-j-1]=t;
    }
     
    //write data into file using fprintf

    fprintf(fp,"%s",str);
    fclose(fp);
}
