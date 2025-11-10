#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    pid_t processid;
    processid=fork();

    if(processid<0)
    {
        printf("Process creation failed.\n");
        exit(1);
    }
    else if(processid==0)
    {
        sleep(5);
        printf("Child process id: %d\n", getpid());
        printf("Childs parent PID after parent exit: %d\n", getppid());
        exit(0);
    }
    else
    {
        printf("Parent Process id: %d\n", getpid());
        exit(0);
    }

    return 0;
}