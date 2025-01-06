#include <stdio.h>

void selectionSort(int arr[], int arr_size)
{
    int sup;
    int minIndex;

    for (int i = 0; i < arr_size - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < arr_size; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        sup = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = sup;
    }
}

int main()
{
    int arr[] = {3, 8, 1, 4, 7, 2, 65, 23};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("ORIGINAL ARRAY:\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n----------------------------\n");

    printf("ARRAY AFTER SELECTION SORT:\n");

    selectionSort(arr, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}