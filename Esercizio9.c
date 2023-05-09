#include <stdio.h>
void main()
{
    /*Progettare un algoritmo che risolva il seguente problema. Si richieda
    all’utente di inserire una serie di terne di dati numerici (A, B, C).
    Il programma deve terminare quando uno dei valori inseriti è minore di
    zero. Si scartino le terne nelle quali i valori non sono in ordine
    strettamente crescente, ovvero quelle terne per cui non valga A < B < C.
    Su tutte le terne non scartate si calcoli il massimo e il minimo dei
    valori inseriti. Si stampino a video tali valori massimi e minimi prima
    di terminare il programma.*/

    int A, B, C, MAX = 0, MIN = 0;

    do
    {
        printf("Inserire il valore A:\n");
        scanf("%d", &A);

        printf("Inserire il valore B:\n");
        scanf("%d", &B);

        printf("Inserire il valore C:\n");
        scanf("%d", &C);

        if (A < B && B < C && A >= 0)
        {
            MIN = A;
            MAX = C;
            if (A < MIN)
            {
                MIN = A;
            }
            if (C > MAX)
            {
                MAX = C;
            }
        }
        else
        {
            printf("Terna non valida\n");
        }
    } while (A >= 0 && B >= 0 && C >= 0);

    printf("MIN: %d\n", MIN);
    printf("MAX: %d\n", MAX);
}