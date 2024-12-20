#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//1
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

//2
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

//3
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

//4
int findDoubles(char arr[], char arrDoubles[])
{
    int doubles = 0;

    for (int i = 0; i<strlen(arr); i++)
    {
        for(int j = 0; j <strlen(arr); j++){
            if(arr[i] == arr[j] && findChar(arrDoubles, arr[i]) == 0){
                arrDoubles[doubles] = arr[i];
                doubles++;
                break;
            }
        }
    }

    return doubles;
}

//1
int lenCompare(char arr1[], char arr2[]){
    if(strlen(arr1)<strlen(arr2))
    {
        return 2;
    }
    else if(strlen(arr1)>strlen(arr2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//2
void charsArray(char arr[], char lettere[]){
    int l = 0;

    for(int i = 0; i<strlen(arr); i++){
        if(findChar(lettere, arr[i]) == 0){
            lettere[l] = arr[i];
            l++;
        }
    }
}

//3
int countVowels(char arr[]){
    int counter = 0; 
    char vowels[] = {95, 65, 101, 69, 105, 73, 111, 79, 117, 85};

    for(int i = 0; i<strlen(arr); i++){
        if(findChar(vowels, arr[i]) != 0){
            counter++;
        }
    }

    return counter;
}

int main()
{
    char string[20];
    char Char;
    char arrPari[10];
    char arrDispari[10];
    int notValid = 0;
   
    printf("-------------------------------------------\n\n");

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
    char arrDoubles[strlen(string)/2];
    int doubles = findDoubles(string, arrDoubles);
    arrDoubles[doubles] ='\0';
    
    printf("\n4)\nCaratteri presenti due o più volte nell'array: ");
    
    if(doubles != 0)
    {
        for(int i=0; i<strlen(arrDoubles); i++)
        {
            printf("%c ", arrDoubles[i]);
        }
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    char string2[20];
    printf("\nInserire seconda stringa: ");
    scanf("%s", string2);
    
    //1
    int sup = lenCompare(string, string2);
    
    printf("\n1)\n");
    
    if(sup == 2)
    {
        printf("L'array più lungo è il secondo inserito\n");
    }
    else if(sup == 1){
        printf("L'array più lungo è il primo inserito\n");
    }
    else
    {
        printf("Gli array hanno la stessa lunghezza\n");
    }
    
    //2
    char lettere1[20];
    char lettere2[20];

    charsArray(string, lettere1);
    charsArray(string2, lettere2);

    printf("\n2)\nLettere in comune: ");
    for(int i = 0; i<strlen(lettere1); i++){
        for(int j = 0; j<strlen(lettere2); j++){
            if(lettere1[i] == lettere2[j]){
                printf("%c ", lettere1[i]);
                break;
            }
        }
    }

    //3
    int vowels1, vowels2;
    vowels1 = countVowels(string);
    vowels2 = countVowels(string2);

    printf("\n\n3)");
    printf("\nVocali del primo array: %d", vowels1);
    printf("\nVocali del secondo array: %d", vowels2);

    if(vowels1>vowels2){
        printf("\nIl primo array contiene più vocali\n");
    }
    else if(vowels1<vowels2){
        printf("\nIl secondo array contiene più vocali\n");
    }
    else{
        printf("\nGli array contengono lo stesso numero di vocali\n");
    }

    int consonants1 = strlen(string)-vowels1;
    int consonants2 = strlen(string2)-vowels2;

    //4
    printf("\n4)");
    printf("\nConsonanti del primo array: %d", consonants1);
    printf("\nConsonanti del secondo array: %d", consonants2);

    if(consonants1>consonants2){
        printf("\nIl primo array contiene più consonanti\n");
    }
    else if(consonants1<consonants2){
        printf("\nIl secondo array contiene più consonanti\n");
    }
    else{
        printf("\nGli array contengono lo stesso numero di consonanti\n");
    }

    printf("\n\n-------------------------------------------\n");

    return 0;
}