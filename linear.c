#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, key, i;
    int *arr;

    // 1. Input array size
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // 2. Dynamically allocate memory
    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!");
        return 0;
    }

    // 3. Input array elements
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Input key element
    printf("Enter key element to search: ");
    scanf("%d", &key);

    // Linear Search
    for (i = 0; i < n; i++) {
        if (arr[i] == key) {
            printf("Key element %d found at index %d\n", key, i + 1);
            free(arr);   // free memory
            return 0;
        }
    }

    printf("Key element %d not found in the array\n", key);

    // 4. Properly free allocated memory
    free(arr);

    return 0;
}