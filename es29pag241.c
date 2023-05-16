#include <stdio.h>
#include <string.h>

void Palindroma(char string[])
{
    int palindroma = 1; 
    char *q; 

    for(int i = 0; i<strlen(string); i++)
    {
        q = &string[i]; 

        if(*q != string[strlen(string)-1-i])
        {
            palindroma = 0; 
            i=strlen(string); 
        }
    }

    if(palindroma == 0)
    {
        printf("La parola non è palindroma\n"); 
    }
    else 
    {
        printf("La parola è palindroma\n"); 
    }
}

int main(int agrc, char *argv[])
{
    char stringa[100]; 

    printf("Inserire una stringa:");
    scanf("%s", stringa);  

    Palindroma(stringa); 

    return 0; 
}