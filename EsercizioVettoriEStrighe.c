/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
int main()
{
    int N, posizione;

    printf("Quanti numeri si vogliono inserire?\n");
    scanf("%d", &N);

    int numeri[N];
    int dispari[N];
    int contaPari = 0, contaDispari = 0, maxPari, minPari, maxDispari, minDispari, doppia;

    for (int i = 0; i < N; i++)
    {
        do
        {
            doppia = 0;
            printf("Inserire un numero (diverso da quelli già inseriti): ");
            scanf("%d", &numeri[i]);

            for (int j = 0; j < i; j++)
            {
                if (numeri[i] == numeri[j])
                {
                    doppia = 1;
                    printf("Valore inserito già presente\n");
                }
            }
        } while (doppia == 1);

        if (numeri[i] % 2 == 0)
        {
            contaPari++;
        }
        else
        {
            dispari[contaDispari] = numeri[i];
            contaDispari++;
        }
    }

    int pari[contaPari];
    int Dispari[contaDispari];
    int p = 0;
    int d = 0;

    for (int i = 0; i < N; i++)
    {
        if (numeri[i] % 2 == 0)
        {
            pari[p] = numeri[i];
            p++;
        }
        else
        {
            dispari[d] = numeri[i];
            d++;
        }
    }

    for (int i = 0; i < contaPari - 1; i++)
    {
        if (pari[i] < pari[i + 1])
        {
            maxPari = pari[i + 1];
        }

        if (pari[i] < pari[i + 1])
        {
            minPari = pari[i];
        }
    }

    for (int i = 0; i < contaDispari - 1; i++)
    {
        if (dispari[i] < dispari[i + 1])
        {
            maxDispari = dispari[i + 1];
        }

        if (dispari[i] < dispari[i + 1])
        {
            minDispari = dispari[i];
        }
    }

    printf(" \n");

    printf("Numeri inseriti:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", numeri[i]);
    }

    printf(" \n");

    printf("Numeri pari inseriti:\n");
    for (int i = 0; i < contaPari; i++)
    {
        printf("%d\n", pari[i]);
    }

    printf(" \n");

    printf("Numeri dispari inseriti:\n");
    for (int i = 0; i < contaDispari; i++)
    {
        printf("%d\n", dispari[i]);
    }

    printf(" \n");

    for (int i = 0; i < N; i++)
    {
        if (maxPari == numeri[i])
        {
            posizione = i;
        }
    }

    printf("Numero pari max: %d, posizione: %d\n", maxPari, posizione);

    for (int i = 0; i < N; i++)
    {
        if (maxDispari == numeri[i])
        {
            posizione = i;
        }
    }

    printf("Numero dispari max: %d, posizione: %d\n", maxDispari, posizione);

    for (int i = 0; i < N; i++)
    {
        if (minPari == numeri[i])
        {
            posizione = i;
        }
    }

    printf("Numero pari min: %d, posizione: %d\n", minPari, posizione);

    for (int i = 0; i < N; i++)
    {
        if (minDispari == numeri[i])
        {
            posizione = i;
        }
    }

    printf("Numero dispari min: %d, posizione: %d\n", minDispari, posizione);

    return 0;
}
