#include <stdio.h>

int main()
{
    int arr[] = {10, 3, 30, 20, 40, 70, 60};
    int n = 7;
    int temp, min;
    printf("array\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        int p = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
            if (arr[i] > arr[i + 1])
            {
                p++;
            }
        }

        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    printf("After Sorting");
    for (int j = 0; j < n; j++)
    {
        printf("%d", arr[j]);
    }
    return 0;
}