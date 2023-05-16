#include <stdio.h>
#include <string.h>
#include <limits.h>

void Funz(int *q, int lungh, int arrayP[], int *p)
{
    for (int i = 0; i < lungh; i++)
    {
        if (*(q + i) % 2 == 0)
        {
            arrayP[*p] = *(q + i);
            (*p)++;
        }
    }
}

int main()
{
    int array[SHRT_MAX];
    int arrayP[SHRT_MAX];
    int var1 = 0, lunghezza; 
    int *q;
    int *p;
    p = &var1; 

    printf("Quanti numeri si vogliono inserire?\n");
    scanf("%d", &lunghezza);

    for (int i = 0; i < lunghezza; i++)
    {
        printf("Inserire un numero:");
        scanf("%d", &array[i]);
    }

    q = array;

    Funz(q, lunghezza, arrayP, p);

    for (int i = 0; i < *p; i++)
    {
        printf("%d ", arrayP[i]);
    }
    printf("\n");

    return 0;
}