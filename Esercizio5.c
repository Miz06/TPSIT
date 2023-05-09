#include <stdio.h>
void main()
{
    /*Progettare un algoritmo che effettui le seguenti operazioni:
    • continui a leggere da tastiera una serie di terne di valori interi A ,
    B e C finchè non vengono inseriti dei valori tali per cui A + B < C
    • conteggi il numero di volte in cui la differenza tra A e B è pari, dispari, e quando è nulla
    • prima di terminare, visualizzi il valore dei valori conteggiati*/

    int A, B, C, diff, p = 0, d = 0, n = 0;

    do
    {
        printf("Inserire il valore A: %d\n");
        scanf("%d", &A);

        printf("Inserire il valore B: %d\n");
        scanf("%d", &B);

        printf("Inserire il valore C: %d\n");
        scanf("%d", &C);

        diff = A - B;

        if (A - B == 0)
        {
            n++;
        }

        if (diff % 2 == 0)
        {
            p++;
        }
        else
        {
            d++;
        }
    } while (A + B >= C);

    printf("Pari: %d\n", p);
    printf("Dispari: %d\n", d);
    printf("nulli: %d\n", n);
}