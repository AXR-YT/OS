#include<stdio.h>
#include<string.h>

struct process {
    char name[20];
    int at, bt, ct, tat, wt;
};

int main() {
    int size = 5;
    struct process p[size];

    // Input
    for (int i = 0; i < size; i++) {
        printf("Enter process name: ");
        scanf("%s", p[i].name);

        printf("Enter AT of %s: ", p[i].name);
        scanf("%d", &p[i].at);

        printf("Enter BT of %s: ", p[i].name);
        scanf("%d", &p[i].bt);
    }

    // Sort by arrival time
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (p[j].at > p[j + 1].at) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // ---- GANTT CHART (PROCESS NAMES) ----
    int cct = 0;
    printf("\nGantt Chart:\n");

    for (int i = 0; i < size; i++) {

        // Idle time
        if (cct < p[i].at) {

            int idle = p[i].at - cct;

            for (int j = 0; j < idle - 1; j++) {
                printf(" ");
            }

            printf("idle");

            for (int j = 0; j < idle - 1; j++) {
                printf(" ");
            }

            printf("|");

            cct = p[i].at;
        }

        // Process block
        for (int j = 0; j < p[i].bt - 1; j++) {
            printf(" ");
        }

        printf("%s", p[i].name);

        for (int j = 0; j < p[i].bt - 1; j++) {
            printf(" ");
        }

        cct = cct + p[i].bt;
    }

    // ---- GANTT CHART (TIME LINE) ----
    printf("\n");

    cct = 0;
    for (int i = 0; i < size; i++) {

        if (cct < p[i].at) {
            cct = p[i].at;
            printf("%d", cct);
        }

        for (int j = 0; j < p[i].bt - 1; j++) {
            printf(" ");
        }

        cct = cct + p[i].bt;
        printf("%d", cct);
    }

    // ---- CT, TAT, WT Calculation ----
    int total_tat = 0;
    int total_wt = 0;
    int t = 0;

    for (int i = 0; i < size; i++) {

        if (t < p[i].at) {
            t = p[i].at;
        }

        t = t + p[i].bt;
        p[i].ct = t;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;

        total_tat = total_tat + p[i].tat;
        total_wt  = total_wt  + p[i].wt;
    }

    // ---- Table Output ----
    printf("\n\nProcess | AT | BT | CT | TAT | WT\n");

    for (int i = 0; i < size; i++) {
        printf("%6s | %2d | %2d | %2d | %3d | %3d\n",
               p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", (float)total_tat / size);
    printf("   Average WT = %.2f\n\n", (float)total_wt / size);

    return 0;
}