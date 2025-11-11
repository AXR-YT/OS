#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    pid_t processid;
    processid=fork();

    if(processid<0)
    {
        printf("Process creation failed!\n");
    }
    else if(processid==0)
    {
        printf("Child process id: %d\n", getpid());
    }
    else
    {
        printf("Parent process id: %d\n", getpid());
        sleep(10);
        printf("******PARENT\n");
        system("ps -axj | tail");
    }

    return 0;
}
