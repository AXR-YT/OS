#include <stdio.h>

int main() {
    int page[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = 12;
    int frames = 4;
    int frame[frames];
    int counter[frames];
    int i, j, k;
    int faults = 0;
    int time = 0;

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        counter[i] = 0;
    }

    for (i = 0; i < n; i++) {
        time++;
        int found = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                found = 1;
                counter[j] = time;
                break;
            }
        }

        if (!found) {
            faults++;

            int index = -1;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    index = j;
                    break;
                }
            }

            if (index != -1) {
                frame[index] = page[i];
                counter[index] = time;
            } else {
                int lru_index = 0;
                int min_time = counter[0];

                for (k = 1; k < frames; k++) {
                    if (counter[k] < min_time) {
                        min_time = counter[k];
                        lru_index = k;
                    }
                }

                frame[lru_index] = page[i];
                counter[lru_index] = time;
            }
        }

        printf("[ ");
        for (k = 0; k < frames; k++) {
            if (frame[k] != -1)
                printf("%d ", frame[k]);
            else
                printf("- ");
        }
        printf("]");

        if (!found)
            printf(" (Fault)");

        printf("\n");
    }

    printf("\n----------------------------------\n");
    printf("Total Page Faults: %d\n", faults);

    return 0;
}