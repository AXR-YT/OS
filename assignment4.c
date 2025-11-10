#include <stdio.h>
#include <string.h>

struct process {
    char process[20];
    int bt;
    int at;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main() {
    struct process p[4], temp;
    int i, j, size = 4;
    int timeline[100]; 
    int time = 0;


    for (i = 0; i < size; i++) {
        printf("Enter the System: name of process %d: ", i + 1);
        scanf("%s", p[i].process);
        printf("Enter the arrival time of %s: ", p[i].process);
        scanf("%d", &p[i].at);
        printf("Enter the burst time of %s: ", p[i].process);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }


    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int total_bt = 0;
    for (i = 0; i < size; i++) {
        total_bt += p[i].bt;
    }

    int smallest;
    for (i = 0; i < total_bt; i++) {
        smallest = -1;
        for (j = 0; j < size; j++) {
            if (p[j].at <= i && p[j].rt > 0) {
                if (smallest == -1 || p[j].rt < p[smallest].rt) {
                    smallest = j;
                }
            }
        }
        if (smallest != -1) {
            timeline[i] = smallest; 
            p[smallest].rt--;
            if (p[smallest].rt == 0) {
                p[smallest].ct = i + 1;
            }
        } else {
            timeline[i] = -1; 
        }
    }

    
    float avgtat = 0, avgwt = 0;
    for (i = 0; i < size; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avgtat += p[i].tat;
        avgwt += p[i].wt;
    }
    avgtat /= size;
    avgwt /= size;


    printf("\nProcess info sorted by arrival time:\n");
    printf(" pro | at | bt | ct | tat | wt \n");
    for (i = 0; i < size; i++) {
        printf(" %s | %d | %d | %d | %d | %d \n", p[i].process, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("avg tat = %.2f\n", avgtat);
    printf("avg wt = %.2f\n", avgwt);

 
    printf("\nGantt Chart:\n|");
    for (i = 0; i < total_bt; i++) {
        if (timeline[i] == -1) {
            printf(" Idle |");
        } else {
            printf(" %s |", p[timeline[i]].process);
        }
    }
    printf("\n");
    printf("0"); 
    for (i = 0; i < total_bt; i++) {
        printf("%5d", i + 1);
    }
    printf("\n");

    return 0;
}