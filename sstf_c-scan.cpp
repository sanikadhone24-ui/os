#include <stdio.h>
#include <stdlib.h>

// Function to sort array
void sort(int arr[], int n) {
    int i, j, temp;

    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    int request[100], cscanReq[100];
    int head, disk_size;

    int totalSeekSSTF = 0;
    int totalSeekCSCAN = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &request[i]);
        cscanReq[i] = request[i];
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    // ---------------- SSTF ----------------
    int visited[100] = {0};
    int headSSTF = head;

    printf("\n--- SSTF Disk Scheduling ---\n");
    printf("Seek Sequence: %d ", headSSTF);

    for(i = 0; i < n; i++) {
        int min = 9999, index = -1;

        for(int j = 0; j < n; j++) {
            if(!visited[j]) {
                int distance = abs(request[j] - headSSTF);

                if(distance < min) {
                    min = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        totalSeekSSTF += min;
        headSSTF = request[index];

        printf("-> %d ", headSSTF);
    }

    printf("\nTotal Seek Time = %d", totalSeekSSTF);
    printf("\nAverage Seek Time = %.2f\n",
           (float)totalSeekSSTF / n);

    // ---------------- C-SCAN ----------------
    int headCSCAN = head;
    int pos;

    sort(cscanReq, n);

    for(i = 0; i < n; i++) {
        if(cscanReq[i] > headCSCAN) {
            pos = i;
            break;
        }
    }

    printf("\n--- C-SCAN Disk Scheduling ---\n");
    printf("Seek Sequence: %d ", headCSCAN);

    // Move towards higher tracks
    for(i = pos; i < n; i++) {
        totalSeekCSCAN += abs(cscanReq[i] - headCSCAN);
        headCSCAN = cscanReq[i];

        printf("-> %d ", headCSCAN);
    }

    // Move to end
    totalSeekCSCAN += abs((disk_size - 1) - headCSCAN);
    headCSCAN = disk_size - 1;

    // Jump to beginning
    totalSeekCSCAN += abs(headCSCAN - 0);
    headCSCAN = 0;

    // Continue servicing remaining requests
    for(i = 0; i < pos; i++) {
        totalSeekCSCAN += abs(cscanReq[i] - headCSCAN);
        headCSCAN = cscanReq[i];

        printf("-> %d ", headCSCAN);
    }

    printf("\nTotal Seek Time = %d", totalSeekCSCAN);
    printf("\nAverage Seek Time = %.2f\n",
           (float)totalSeekCSCAN / n);

    return 0;
}