#include <stdio.h>
#include <math.h>

int main() {
    int memorySize, processSize;
    int blockSize, remaining;

    printf("Enter total memory size: ");
    scanf("%d", &memorySize);

    printf("Enter process size: ");
    scanf("%d", &processSize);

    // Find smallest power of 2 block size
    blockSize = 1;

    while(blockSize < processSize) {
        blockSize = blockSize * 2;
    }

    // Check allocation possibility
    if(blockSize > memorySize) {
        printf("\nMemory allocation failed!");
    }
    else {
        remaining = memorySize - blockSize;

        printf("\n--- Buddy System Allocation ---\n");
        printf("Process Size = %d KB\n", processSize);
        printf("Allocated Block Size = %d KB\n", blockSize);
        printf("Remaining Memory = %d KB\n", remaining);
    }

    return 0;
}