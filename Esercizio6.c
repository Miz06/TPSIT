#include <stdio.h>
void main()
{
    /*Progettare un algoritmo che effettui le seguenti operazioni:
    • legga da tastiera una coppia di valori interi A e B con A<B;
    • continui a leggere da tastiera una serie di valori interi, terminando
    quando il valore letto è al di fuori dell’intervallo [A, B];
    • conteggi la media dei valori letti;
    • prima di terminare, stampi il valore calcolato.*/

    int A, B, n, i = 0, somma = 0;
    double media;

    do
    {
        printf("Inserire il valore A:\n");
        scanf("%d", &A);

        printf("Inserire il valore B:\n");
        scanf("%d", &B);

    } while (B < A);

    do
    {
        printf("Inserire un valore: \n");
        scanf("%d", &n);

        if (n >= A && n <= B)
        {
            i++;
            somma = somma + n;
        }

    } while (n >= A && n <= B);

    media = (double)somma / (double)i;

    printf("La media dei valori inseriti è: %f\n", media);
}