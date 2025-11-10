#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

void frokeaxmple()
{
    if(fork()==0)
    {
        printf("The child's process id is %d\n", getpid());
    }
    else
    {
        printf("The parent's process id is %d\n", getpid());
    }
}

int main()
{
    frokeaxmple();

    return 0;
}