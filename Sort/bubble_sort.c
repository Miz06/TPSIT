#include <stdio.h>

void bubbleSort(int arr[], int arr_size)
{
    int sup;

    for (int i = 0; i < arr_size-1; i++)
    {
        for (int j = i+1; j < arr_size; j++)
        {
            if(arr[i] > arr[j]){
                sup = arr[j];
                arr[j] = arr[i];
                arr[i] = sup;
            }
        }
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

    printf("ARRAY AFTER BUBBLE SORT:\n");

    bubbleSort(arr, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}