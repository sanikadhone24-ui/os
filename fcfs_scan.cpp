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
    int request[100], scanReq[100];
    int head, disk_size;

    int totalSeekFCFS = 0;
    int totalSeekSCAN = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &request[i]);
        scanReq[i] = request[i];
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    // ---------------- FCFS ----------------
    int headFCFS = head;

    printf("\n--- FCFS Disk Scheduling ---\n");
    printf("Seek Sequence: %d ", headFCFS);

    for(i = 0; i < n; i++) {
        totalSeekFCFS += abs(request[i] - headFCFS);
        headFCFS = request[i];

        printf("-> %d ", headFCFS);
    }

    printf("\nTotal Seek Time = %d", totalSeekFCFS);
    printf("\nAverage Seek Time = %.2f\n",
           (float)totalSeekFCFS / n);

    // ---------------- SCAN ----------------
    int headSCAN = head;
    int pos;

    sort(scanReq, n);

    for(i = 0; i < n; i++) {
        if(scanReq[i] > headSCAN) {
            pos = i;
            break;
        }
    }

    printf("\n--- SCAN Disk Scheduling ---\n");
    printf("Seek Sequence: %d ", headSCAN);

    // Move towards higher tracks
    for(i = pos; i < n; i++) {
        totalSeekSCAN += abs(scanReq[i] - headSCAN);
        headSCAN = scanReq[i];

        printf("-> %d ", headSCAN);
    }

    // Move to end of disk
    totalSeekSCAN += abs((disk_size - 1) - headSCAN);
    headSCAN = disk_size - 1;

    // Reverse direction
    for(i = pos - 1; i >= 0; i--) {
        totalSeekSCAN += abs(scanReq[i] - headSCAN);
        headSCAN = scanReq[i];

        printf("-> %d ", headSCAN);
    }

    printf("\nTotal Seek Time = %d", totalSeekSCAN);
    printf("\nAverage Seek Time = %.2f\n",
           (float)totalSeekSCAN / n);

    return 0;
}