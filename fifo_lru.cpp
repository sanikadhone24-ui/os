#include <stdio.h>

int main() {
    int pages[100], frames[10];
    int n, f, i, j, k;
    int pageFaultsFIFO = 0, pageFaultsLRU = 0;

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
            pageFaultsFIFO++;
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

    printf("Total Page Faults = %d\n", pageFaultsFIFO);

    // ---------------- LRU ----------------
    for(i = 0; i < f; i++) {
        frames[i] = -1;
    }

    int time[10] = {0}, counter = 0;

    printf("\n--- LRU Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        int found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found) {
            int pos = -1;

            for(j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if(pos == -1) {
                int min = time[0];
                pos = 0;

                for(j = 1; j < f; j++) {
                    if(time[j] < min) {
                        min = time[j];
                        pos = j;
                    }
                }
            }

            counter++;
            frames[pos] = pages[i];
            time[pos] = counter;
            pageFaultsLRU++;
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

    printf("Total Page Faults = %d\n", pageFaultsLRU);

    return 0;
}