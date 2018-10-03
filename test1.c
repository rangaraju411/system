#include<stdio.h>
#include <malloc.h>

void func(int a)
{
        if(a == 1)
                printf("a is 1\n");
        else
                printf("a is 0\n");
}

int main()
{
        int *ptr = malloc(100);
        int *ptr1 = malloc(100);
        func(0);
        func(1);
        free(ptr1);
        free(ptr1);// Intentional double free
}
                                                                                                                                                                         
