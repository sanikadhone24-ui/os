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

    // ---------------- First Fit ----------------
    int allocationFF[20];

    for(i = 0; i < n; i++)
        allocationFF[i] = -1;

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(b[j] >= p[i]) {
                allocationFF[i] = j;
                b[j] -= p[i];
                break;
            }
        }
    }

    printf("\n--- First Fit Allocation ---\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, p[i]);

        if(allocationFF[i] != -1)
            printf("%d\n", allocationFF[i] + 1);
        else
            printf("Not Allocated\n");
    }

    // ---------------- Best Fit ----------------
    int allocationBF[20];

    for(i = 0; i < n; i++) {
        allocationBF[i] = -1;
        b[i] = temp[i];
    }

    for(i = 0; i < n; i++) {
        int bestIdx = -1;

        for(j = 0; j < m; j++) {
            if(b[j] >= p[i]) {
                if(bestIdx == -1 || b[j] < b[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if(bestIdx != -1) {
            allocationBF[i] = bestIdx;
            b[bestIdx] -= p[i];
        }
    }

    printf("\n--- Best Fit Allocation ---\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, p[i]);

        if(allocationBF[i] != -1)
            printf("%d\n", allocationBF[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}