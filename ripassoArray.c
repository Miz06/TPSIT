#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void popolaArray(int vett[])
{
    for (int i = 0; i < 10; i++)
    {
        vett[i] = rand() % 30;
    }
}

void stampaArray(int vett[])
{ //1
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d) %d\n", i, vett[i]);
    }
}

void stampaArrayInverso(int vett[])
{ //2
    printf("\n");
    for (int i = 9; i > -1; i--)
    {
        printf("%d) %d\n", i, vett[i]);
    }
}

int somma(int vett[])
{//3
    int somma = 0;
    
    for(int i = 0; i<10; i++){
        somma += vett[i];
    }
    
    return somma;
}

double media(int somma)
{//3
    return somma/10;
}

void stampaPari(int vett[])
{//4
    for(int i = 0; i<10; i++)
    {
        if(vett[i] % 2 == 0){
            printf("%d\n", vett[i]);
        }
    }
}

void stampaDispari(int vett[])
{//5
    for(int i = 0; i<10; i++)
    {
        if(vett[i] % 2 != 0){
            printf("%d\n", vett[i]);
        }
    }
}

int cercaNum(int vett[], int num)
{//6
    int found = -1; 

    for(int i = 0; i<10; i++){
        if(num == vett[i]){
            found = i;
            i = 10;
        }
    }

    return found;
}

int main()
{
    int arr[10];
    srand(time(0));
    int choice;

    popolaArray(arr);

    do
    {
        printf("\n-----------------------------\n");
        printf("[1] Visualizza'larray\n");
        printf("[2] Visualizza'larray con ordinamento contrario\n");
        printf("Scelta: ");
        scanf("%d", &choice);

        if (choice != 0)
        {
            if (choice == 1)
            {
                stampaArray(arr);
            }
            else if (choice == 2)
            {
                stampaArrayInverso(arr);
            }
            else if(choice == 3)
            {
                int Somma = somma(arr);
                printf("\nSomma: %d\n", Somma);
                printf("Media: %f\n", media(Somma));
            }
            else if(choice == 4)
            {
                printf("\n");
                stampaPari(arr);
            }
            else if(choice == 5){
                printf("\n");
                stampaDispari(arr);
            }
            else if(choice == 6){
                int numRicerca; 

                printf("\nNumero che si desidera ricercare: ");
                scanf("%d", &numRicerca);

                int position = cercaNum(arr, numRicerca);

                if(position == -1)
                {
                    printf("Numero non presente nell'array\n");
                }
                else{
                    printf("Il numero si trova in posizione %d\n", position);
                }
            }
        }
    } while (choice != 0);

    return 0;
}