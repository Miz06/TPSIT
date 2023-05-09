#include <stdio.h>
#include <math.h>
void main()
{
    /*Progettare un algoritmo che effettui la lettura da tastiera di una serie
    di coppie di valori numerici reali (sia positivi che negativi che zero).
    Per ciascuna coppia, l’algoritmo deve calcolare e stampare il valore
    della radice quadrata del rapporto tra il valore maggiore e quello
    minore dei due. Il programma termina quando vengono inseriti dei valori
    che non permettono di svolgere il calcolo nel dominio dei numeri reali.
    Prima di terminare si richiede di stampare un messaggio che indichi la
    ragione per cui non è stato possibile svolgere il calcolo.*/

    int val1, val2;
    double rapporto = 0, radice = 0;

    do
    {
        printf("Inserire il valore 1:\n");
        scanf("%d", &val1);

        printf("Inserire il valore 2:\n");
        scanf("%d", &val2);

        if (val1 > val2)
        {
            rapporto = (double)val1 / (double)val2;
        }
        else
        {
            rapporto = (double)val2 / (double)val1;
        }

        if (rapporto >= 0)
        {
            radice = sqrt(rapporto);
            printf("La radice quadrata del rapporto tra i due valori inseriti è: %f\n", radice);
        }
    } while (rapporto >= 0);

    prinf("Non è possibile calcolare la radice quadrata di un numero negativo\n");
}