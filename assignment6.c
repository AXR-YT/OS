// cd "/mnt/c/Users/hp/Downloads/os"
//  gcc semaphore.c -o semaphore
//   ./semaphore
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t mutex, wrt;
int sharedvar = 99;
int readercount = 0;
pthread_t writers[10], readers[10];


void *reader(void *param)
{
    sem_wait(&mutex);
    readercount++;
    if (readercount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("\n%d reader is reading sharedvar=%d", readercount, sharedvar);
    sleep(1);
    sem_wait(&mutex);
    readercount--;
    if (readercount == 0)
        sem_post(&wrt);
    sem_post(&mutex);

    printf("\n%d Reader is done", readercount + 1);
   
}


void *writer(void *param)
{
    printf("\nWriter is trying to enter");
    sem_wait(&wrt);
    printf("\nWriter has entered CS");
    sharedvar++;
    printf("\nWriter CHANGED THE VALUE OF SHARED VAR TO %d", sharedvar);
    sem_post(&wrt);
    printf("\nWriter is out of CS\n");
   
}


int main()
{
    int n2, i;
    printf("Enter the number of readers: ");
    scanf("%d", &n2);

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < n2; i++)
    {
        pthread_create(&readers[i], NULL, reader, NULL);
        pthread_create(&writers[i], NULL, writer, NULL);
        
    }

    for (i = 0; i < n2; i++)
    {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}