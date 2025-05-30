#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void stampaArray(int vett[], int len)
{ // 1
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d) %d\n", i, vett[i]);
    }
}

void stampaArrayInverso(int vett[], int len)
{ // 2
    printf("\n");
    for (int i = len - 1; i > -1; i--)
    {
        printf("%d) %d\n", i, vett[i]);
    }
}

int somma(int vett[], int len)
{ // 3
    int somma = 0;

    for (int i = 0; i < len; i++)
    {
        somma += vett[i];
    }

    return somma;
}

double media(int somma)
{ // 3
    return (double)somma / 10;
}

void stampaPari(int vett[], int len)
{ // 4
    for (int i = 0; i < len; i++)
    {
        if (vett[i] % 2 == 0)
        {
            printf("%d\n", vett[i]);
        }
    }
}

void stampaDispari(int vett[], int len)
{ // 5
    for (int i = 0; i < len; i++)
    {
        if (vett[i] % 2 != 0)
        {
            printf("%d\n", vett[i]);
        }
    }
}

int cercaNum(int vett[], int num, int len)
{ // 6
    for (int i = 0; i < len; i++)
    {
        if (num == vett[i])
        {
            return i;
        }
    }

    return -1;
}

int rimuoviElemento(int vett[], int num, int len)
{ // 7
    int found;

    found = cercaNum(vett, num, len);

    if (found != -1)
    {
        for (int i = found; i < len - 1; i++)
        {
            vett[i] = vett[i + 1];
        }

        vett[len - 1] = -1;
    }

    return found;
}

void invertiCoppie(int vett[], int len)
{ // 8
    int sup;

    if (len % 2 == 0)
    {
        for (int i = 0; i < len; i += 2)
        {
            sup = vett[i];
            vett[i] = vett[i + 1];
            vett[i + 1] = sup;
        }
    }
    else
    {
        for (int i = 0; i < len - 1; i += 2)
        {
            sup = vett[i];
            vett[i] = vett[i + 1];
            vett[i + 1] = sup;
        }
    }
}

void bubbleSort(int vett[], int len)
{//9
    int sup;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (vett[i] > vett[j])
            {
                sup = vett[j];
                vett[j] = vett[i];
                vett[i] = sup;
            }
        }
    }
}

void popolaArray(int vett[], int len)
{
    int sup;
    int elementiPopolati =1;

    vett[0] = rand()%30;

    for (int i = 1; i < len; i++)
    {
        do
        {
            sup = rand() % 30;
        } while (cercaNum(vett, sup, elementiPopolati) != -1);

        vett[i] = sup;
        elementiPopolati++;
    }
}

int main()
{
    int len;
    int choice;
    srand(time(0));

    printf("Grandezza array: ");
    scanf("%d", &len);

    int arr[10];

    popolaArray(arr, len);

    do
    {
        printf("\n-----------------------------\n");
        printf("[1] Visualizza array\n");
        printf("[2] Visualizza ordinamento opposto\n");
        printf("[3] Somma e media\n");
        printf("[4] Visualizza numeri pari\n");
        printf("[5] Visualizza numeri dispari\n");
        printf("[6] Ricerca numero\n");
        printf("[7] Elimina elemento\n");
        printf("[8] Inverti ordine a coppie\n");
        printf("[9] Bubble sort\n");
        printf("[0] Esci\n");
        printf("Scelta: ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 9)
        {
            printf("Errore. Inserire un numero relativo alle opzioni proposte.");
        }
        if (choice != 0)
        {
            if (choice == 1)
            {
                stampaArray(arr, len);
            }
            else if (choice == 2)
            {
                stampaArrayInverso(arr, len);
            }
            else if (choice == 3)
            {
                int Somma = somma(arr, len);
                printf("\nSomma: %d\n", Somma);
                printf("Media: %f\n", media(Somma));
            }
            else if (choice == 4)
            {
                printf("\n");
                stampaPari(arr, len);
            }
            else if (choice == 5)
            {
                printf("\n");
                stampaDispari(arr, len);
            }
            else if (choice == 6)
            {
                int numRicerca;

                printf("\nNumero che si desidera ricercare: ");
                scanf("%d", &numRicerca);

                int position = cercaNum(arr, numRicerca, len);

                if (position == -1)
                {
                    printf("Numero non presente nell'array\n");
                }
                else
                {
                    printf("Il numero si trova in posizione %d\n", position);
                }
            }
            else if (choice == 7)
            {
                int num;

                printf("\nNumero da rimuovere: ");
                scanf("%d", &num);

                if (rimuoviElemento(arr, num, len) != -1)
                {
                    len--;
                }
                else
                {
                    printf("Numero non presente nell'array\n");
                }
            }
            else if (choice == 8)
            {
                invertiCoppie(arr, len);
            }
            else if (choice == 9)
            {
                bubbleSort(arr, len);
                stampaArray(arr, len);
            }
        }
    } while (choice != 0 || choice < 0 || choice > 9);

    return 0;
}