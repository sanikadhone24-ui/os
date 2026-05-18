#include <stdio.h>

int main() {
    int pageSize, logicalAddress;
    int pageNumber, offset;
    int frameNumber, physicalAddress;

    printf("Enter page size: ");
    scanf("%d", &pageSize);

    printf("Enter logical address: ");
    scanf("%d", &logicalAddress);

    // Calculate page number and offset
    pageNumber = logicalAddress / pageSize;
    offset = logicalAddress % pageSize;

    printf("Enter frame number for page %d: ", pageNumber);
    scanf("%d", &frameNumber);

    // Calculate physical address
    physicalAddress = (frameNumber * pageSize) + offset;

    printf("\n--- Address Translation Using Paging ---\n");
    printf("Logical Address = %d\n", logicalAddress);
    printf("Page Number = %d\n", pageNumber);
    printf("Offset = %d\n", offset);
    printf("Frame Number = %d\n", frameNumber);
    printf("Physical Address = %d\n", physicalAddress);

    return 0;
}