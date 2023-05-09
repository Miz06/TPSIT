#include <stdio.h>

int main()
{
/*Es2
Scrivere un programma in C che dopo aver inserito una stringa ed un carattere  da linea comando, 
elimini il carattere inserito dalla stringa stessa (se esistente).*/

    char str[100]; 
    char car; 
    int presente = 0; 

    printf("Inserire una parola:");
    scanf("%s", str);  

    printf("Inserire il carattere che si vuole eliminare:"); 
    scanf("%s", &car); 

    for (int i = 0; i<100; i++)
    {
        if (car == str[i])
        {
            for(int j = i; j<100; j++)
            {
                str[j] = str[j+1]; 
            }
            presente = 1; 
        }
        if (car == str[i])
        {
            for(int j = i; j<100; j++)
            {
                str[j] = str[j+1]; 
            }
            presente = 1; 
        }
    }

    if (presente == 1)
    {
        printf("%s", str); 
    }
    else
    {
        printf("Il carattere non è contenuto all'interno della stringa"); 
    }
    return 0;
}
