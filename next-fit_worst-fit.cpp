#include <stdio.h>

int main() {
    int b[20], p[20], temp[20];
    int m, n, i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter size of memory blocks:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        temp[i] = b[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter size of processes:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    // ---------------- Next Fit ----------------
    int allocationNF[20];

    for(i = 0; i < n; i++)
        allocationNF[i] = -1;

    int lastAllocated = 0;

    for(i = 0; i < n; i++) {
        int count = 0;

        while(count < m) {
            if(b[lastAllocated] >= p[i]) {
                allocationNF[i] = lastAllocated;
                b[lastAllocated] -= p[i];
                break;
            }

            lastAllocated = (lastAllocated + 1) % m;
            count++;
        }
    }

    printf("\n--- Next Fit Allocation ---\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, p[i]);

        if(allocationNF[i] != -1)
            printf("%d\n", allocationNF[i] + 1);
        else
            printf("Not Allocated\n");
    }

    // Restore original blocks
    for(i = 0; i < m; i++) {
        b[i] = temp[i];
    }

    // ---------------- Worst Fit ----------------
    int allocationWF[20];

    for(i = 0; i < n; i++)
        allocationWF[i] = -1;

    for(i = 0; i < n; i++) {
        int worstIdx = -1;

        for(j = 0; j < m; j++) {
            if(b[j] >= p[i]) {
                if(worstIdx == -1 || b[j] > b[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if(worstIdx != -1) {
            allocationWF[i] = worstIdx;
            b[worstIdx] -= p[i];
        }
    }

    printf("\n--- Worst Fit Allocation ---\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, p[i]);

        if(allocationWF[i] != -1)
            printf("%d\n", allocationWF[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}