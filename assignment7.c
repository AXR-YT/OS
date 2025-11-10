#include <stdio.h>

int main() {
    int p_no;
    printf("Enter number of processes: ");
    scanf("%d", &p_no);

    int allocation[p_no][3];
    int max[p_no][3];
    int available[3];

    // Input Allocation
    printf("\n--- Allocation Matrix Input ---\n");
    for (int i = 0; i < p_no; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Allocation for P%d R%d: ", i, j);
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max
    printf("\n--- Max Matrix Input ---\n");
    for (int i = 0; i < p_no; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Max for P%d R%d: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    // Available
    printf("\n--- Available Resources ---\n");
    for (int j = 0; j < 3; j++) {
        printf("Available R%d: ", j);
        scanf("%d", &available[j]);
    }

    // Need Matrix
    int need[p_no][3];
    printf("\n--- Need Matrix ---\n");
    for (int i = 0; i < p_no; i++) {
        for (int j = 0; j < 3; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Safety Algorithm
    int finish[p_no];
    int sequence[p_no];
    int work[3];

    for (int i = 0; i < p_no; i++)
        finish[i] = 0;

    for (int j = 0; j < 3; j++)
        work[j] = available[j];

    int count = 0;
    int safe = 0;

    while (count < p_no) {
        int found = 0;

        for (int i = 0; i < p_no; i++) {
            if (!finish[i]) {
                int can_run = 1;

                for (int j = 0; j < 3; j++) {
                    if (need[i][j] > work[j]) {
                        can_run = 0;
                        break;
                    }
                }

                if (can_run) {
                    for (int j = 0; j < 3; j++) {
                        work[j] += allocation[i][j];
                    }

                    sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nDeadlock possible. System is NOT safe.\n");
            safe = 0;
            break;
        }

        safe = 1;
    }

    // Initial safe sequence print
    if (safe) {
        printf("\nSafe Sequence: ");
        for (int i = 0; i < p_no; i++)
            printf("P%d ", sequence[i]);
        printf("\n");
    }

    // Request Section
    char condition;
    printf("\nDo you want to request resources? (y/n): ");
    scanf(" %c", &condition);

    if (condition == 'y') {
        int process;
        int request[3];

        printf("Enter process number (0-%d): ", p_no - 1);
        scanf("%d", &process);

        printf("Enter request for P%d:\n", process);
        for (int j = 0; j < 3; j++) {
            printf("Request R%d: ", j);
            scanf("%d", &request[j]);
        }

        // Condition 1
        for (int j = 0; j < 3; j++) {
            if (request[j] > need[process][j]) {
                printf("\nERROR: Request exceeds NEED.\n");
                return 0;
            }
        }

        // Condition 2
        for (int j = 0; j < 3; j++) {
            if (request[j] > available[j]) {
                printf("\nProcess must WAIT. Resources not available.\n");
                return 0;
            }
        }

        // Pretend allocation
        for (int j = 0; j < 3; j++) {
            available[j] -= request[j];
            allocation[process][j] += request[j];
            need[process][j] -= request[j];
        }

        // Safety check (again)
        for (int j = 0; j < 3; j++)
            work[j] = available[j];

        for (int i = 0; i < p_no; i++)
            finish[i] = 0;

        count = 0;
        safe = 0;

        while (count < p_no) {
            int found = 0;

            for (int i = 0; i < p_no; i++) {
                if (!finish[i]) {
                    int can_run = 1;

                    for (int j = 0; j < 3; j++) {
                        if (need[i][j] > work[j]) {
                            can_run = 0;
                            break;
                        }
                    }

                    if (can_run) {
                        for (int j = 0; j < 3; j++)
                            work[j] += allocation[i][j];

                        sequence[count++] = i;
                        finish[i] = 1;
                        found = 1;
                    }
                }
            }

            if (!found) {
                safe = 0;
                break;
            }

            safe = 1;
        }

        if (safe) {
            printf("\nRequest GRANTED. System remains SAFE.\n");
            printf("New Safe Sequence: ");
            for (int i = 0; i < p_no; i++)
                printf("P%d ", sequence[i]);
            printf("\n");
        } else {
            // Rollback
            for (int j = 0; j < 3; j++) {
                available[j] += request[j];
                allocation[process][j] -= request[j];
                need[process][j] += request[j];
            }
            printf("\nRequest DENIED. System would become UNSAFE.\n");
        }
    }

    return 0;
}