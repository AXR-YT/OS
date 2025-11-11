#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int parentarr[]={2,3,5,1,6,3,2};
int childarr[]={4,2,7,4,1,9,3};
int n=7;

void bubblesort_child(int arr[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]<arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

    printf("Child process in descending order: \n");
}

void bubblesort_parent(int arr[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j+1]<arr[j])
            {
                int temp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
            }
        }
    }

    printf("Parent process in ascending order: \n");
}

void display(int arr[])
{
    for(int i=0;i<n;i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    pid_t process_id;
    process_id=fork();

    if(process_id<0)
    {
        printf("\nFailed to create a new process!");
    }
    else if(process_id==0)
    {
        printf("Child process with pid: %d\n", getpid());
        bubblesort_child(childarr, n);
        display(childarr);
    }
    else
    {
        printf("Parent process id: %d\n", getpid());
        bubblesort_parent(parentarr, n);
        display(parentarr);
    }

    return 0;
}
