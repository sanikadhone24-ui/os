#include <stdio.h>

int main() {
    int pages[100], frames[10];
    int n, f, i, j, k;

    int fifoFaults = 0, optimalFaults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // ---------------- FIFO ----------------
    for(i = 0; i < f; i++) {
        frames[i] = -1;
    }

    int index = 0;

    printf("\n--- FIFO Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        int found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            fifoFaults++;
        }

        printf("Frames: ");
        for(j = 0; j < f; j++) {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", fifoFaults);

    // ---------------- Optimal ----------------
    for(i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\n--- Optimal Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        int found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            int pos = -1;

            // Empty frame available
            for(j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // Find optimal replacement
            if(pos == -1) {
                int farthest = -1, indexReplace = -1;

                for(j = 0; j < f; j++) {
                    int nextUse = 9999;

                    for(k = i + 1; k < n; k++) {
                        if(frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > farthest) {
                        farthest = nextUse;
                        indexReplace = j;
                    }
                }

                pos = indexReplace;
            }

            frames[pos] = pages[i];
            optimalFaults++;
        }

        printf("Frames: ");
        for(j = 0; j < f; j++) {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", optimalFaults);

    return 0;
}