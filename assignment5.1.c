#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define MAX 100

int main() {
    int filedes[2];      // Only ONE pipe: Parent → Child
    pid_t pid;
    char string[MAX];
    char line[MAX];
    int n;

    // Create only ONE pipe (filedes)
    if (pipe(filedes) < 0) {
        printf("Pipe creation error\n");
        exit(0);
    }

    if ((pid = fork()) < 0) {
        printf("Fork error\n");
        exit(0);
    }

    if (pid > 0) {
        // PARENT: Write only
        close(filedes[0]);  // Close read end

        printf("Enter the string to send to child: ");
        fgets(string, MAX, stdin);
        string[strcspn(string, "\n")] = 0;  // Remove newline

        write(filedes[1], string, strlen(string) + 1);

        printf("Parent sent: %s\n", string);

        close(filedes[1]);
        wait(NULL);  // Prevent zombie
    }
    else {
        // CHILD: Read only
        close(filedes[1]);  // Close write end

        n = read(filedes[0], line, MAX);
        line[n] = '\0';

        printf("Child received: %s\n", line);

        close(filedes[0]);
        _exit(0);
    }

    return 0;
}