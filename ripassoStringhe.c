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

int findDoubles(char arr[], char arrDoubles[])
{
    int doubles = 0;

    for (int i = 0; i<strlen(arr); i++)
    {
        for(int j = i+1; j <strlen(arr); j++){
            if(i != 0)
            if(arr[i] == arr[j] && findChar(arrDoubles, arr[i]) == 0){
                arrDoubles[doubles] = arr[i];
                doubles++;
                break;
            }
        }
    }

    return doubles;
}

int lenCompare(char arr1[], char arr2[])
    if(strlen(arr1)<strlen(arr2))
    {
        return 2;
    }
    else if(strlen(arr1)>strlen(arr2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
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
    
    printf("%d", strlen(string));
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
    char arrDoubles[strlen(string)/2];
    int doubles = findDoubles(string, arrDoubles);
    arrDoubles[doubles] ='\0';
    
    printf("\n4)\n");
    
    if(doubles != 0)
    {
        for(int i=0; i<strlen(arrDoubles); i++)
        {
            printf("Il carattere %c è presente due o più volte nell'array\n", arrDoubles[i]);
        }
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    char string2[20];
    printf("Inserire seconda stringa: ");
    scanf("%s", string2);
    
    int sup = lenCompare(string, string2);
    
    if()
    
    printf("----------------------------------\n");

    return 0;
}