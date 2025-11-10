#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main() {
    int filedes[2];
    int filedes2[2];
    pid_t pid;
    char string[MAX];
    char line[MAX];
    int n;

    if (pipe(filedes) < 0 || pipe(filedes2) < 0) {
        printf("Pipe creation error\n");
        exit(0);
    }

   ;

    if ( (pid = fork()) < 0) {
        printf("Fork error\n");
        exit(0);
    }

    if (pid > 0) {
        close(filedes[0]);
        close(filedes2[1]);

        printf("Enter the string to send to child: ");
        fgets(string, MAX, stdin);
        write(filedes[1], string, MAX);

        n = read(filedes2[0], line, MAX);
        line[n] = '\0';
        printf("Parent received reply: %s\n", line);

        close(filedes[1]);
        close(filedes2[0]);
    } 
    else {
        close(filedes[1]);
        close(filedes2[0]);

        n = read(filedes[0], line, MAX);
        line[n] = '\0';
        printf("Child received: %s\n", line);

        printf("Enter reply for parent: ");
        fgets(string, MAX, stdin);
        write(filedes2[1], string, MAX);

        close(filedes[0]);
        close(filedes2[1]);
    }

    return 0;
}