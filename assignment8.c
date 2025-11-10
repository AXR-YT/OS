#include <stdio.h>

int main() {
    int page[] = {1,2,3,4,1,2,5,1,2,3,4,5};
    int n = 12;
    int frames = 4;
    int frame[4] = {-1,-1,-1,-1};
    int i, j, k;
    int pos = 0;   // FIFO pointer
    int found, faults = 0;

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already present
        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                found = 1;
                break;
            }
        }

        // Page fault occurs
        if (found == 0) {
            frame[pos] = page[i];  // Replace using FIFO
            pos = (pos + 1) % frames;
            faults++;
        }

        // Print frame status
        printf("Frames: ");
        for (k = 0; k < frames; k++) {
            if (frame[k] != -1)
                printf("%d ", frame[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", faults);

    return 0;
}