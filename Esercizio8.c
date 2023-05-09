#include <stdio.h>
#include <math.h>
void main()
{
    /*Progettare un algoritmo che risolve il seguente problema. Si desidera
    calcolare la somma delle radici quadrate di N valori numerici inseriti
    dall’utente, con N inserito in input.
    L’algoritmo deve stampare la somma calcolata. L’algoritmo deve terminare
    con un messaggio di errore quando viene inserito un numero che non
    permette di effettuare il calcolo (nel dominio dei numeri reali).*/

    int N, n, i = 0; 
    double somma = 0;

    printf("Inserire il numero di numeri di cui si vuole calcolare la somma delle radici quadrate: \n");
    scanf("%d", &N);

    do
    {
        printf("Inserire un numero: \n");
        scanf("%d", &n);

        if (n >= 0)
        {
            i++;
            somma = somma + sqrt(n);
        }
        else
        {
            printf("Hai inserito un numero negativo di cui non è quindi possibile calcolare la radice quadrata \n");
        }
    } while (n >= 0 && i < N);

    printf("La somma dei numeri inseriti è: %f\n", somma);
}