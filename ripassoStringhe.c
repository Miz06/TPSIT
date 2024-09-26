// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int findChar(char arr[], char Char)
{
    int counter = 0;

    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == Char)
        {
            counter++;
        }
    }

    return counter;
}

int elementiArray(char arr[])
{
    for (int i = 0; i < strlen(arr); i++)
    {
        if (isdigit(arr[i]))
        {
            return 1;
        }
    }

    return 0;
}

void createArray(char arr[], char arrPari[], char arrDispari[])
{
    int pariIndex = 0;
    int dispariIndex = 0;

    for (int i = 0; i < strlen(arr); i++)
    {
        if (i % 2 == 0)
        {
            arrPari[pariIndex] = arr[i];
            pariIndex++;
        }
        else
        {
            arrDispari[dispariIndex] = arr[i];
            dispariIndex++;
        }
    }

    arrPari[pariIndex] = '\0';
    arrDispari[dispariIndex] = '\0';
}

int findDoubles(char arr[])
{
    char arrDoubles[strlen(arr)/2];
    int noDoubles = 0;

    for (int i = 0; i<strlen(arr); i++)
    {
        for(int j = i+1; j <strlen(arr); j++){
            if(i != 0)
            if(arr[i] == arr[j]){
                printf("Il carattere %c è presente due o più volte nell'array\n", arr[i]);
                noDoubles = 1;
                break;
            }
        }
    }

    return noDoubles;

}

int main()
{
    char string[20];
    char Char;
    char arrPari[10];
    char arrDispari[10];
    int notValid = 0;

    printf("----------------------------------\n");

    //1

    printf("1)\n");
    do
    {
        printf("Inserimento stringa: ");
        scanf("%s", string);

        notValid = elementiArray(string);

        if (notValid == 1)
        {
            printf("Errore: uno o più numeri sono stati inseriti nell'array\n");
        }

    } while (notValid == 1);

    // 2
    printf("\n2)\nCarattere da ricercare:");
    scanf(" %c", &Char);

    int counter = findChar(string, Char);

    if (counter == 0)
    {
        printf("Carattere non presente nell'array\n");
    }
    else
    {
        printf("Carattere presente %d volte nell'array\n", counter);
    }

    // 3
    createArray(string, arrPari, arrDispari);

    printf("\n3)\nCaratteri in posizione pari: %s\n", arrPari);
    printf("Caratteri in posizione dispari: %s\n", arrDispari);

    //4
    printf("\n4)\n");
    if(findDoubles(string) == 0){
        printf("Non sono presenti doppi elementi all'interno dell'array");
    }

    printf("----------------------------------\n");

    return 0;
}