#include <stdio.h>
#include <string.h>

int main(int agrc, char *argv[])
{//Alessandro Mizzon 
    char stringa[100]; 
    char *q; 
    int palindroma = 1; 

    printf("Inserire una stringa:");
    scanf("%s", stringa);  

    for(int i = 0; i<strlen(stringa); i++)
    {
        q = &stringa[i]; 

        if(*q != stringa[strlen(stringa)-1-i])
        {
            palindroma = 0; 
            i=strlen(stringa); 
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
