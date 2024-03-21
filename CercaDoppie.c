#include <stdio.h>
#include <string.h>
int main() //Alessandro Mizzon 
{
    char parola[100]; 
    int i = 1; 
    int doppia = 1; 

    printf("Inserire una parola: ");
    scanf("%s", parola);

    do
    {
        if (parola[i] == parola[i - 1])
        {
            doppia = 0;
        }
        i++;
    } while (i < 100 && doppia == 0);

    if (doppia == 0)
    {
        printf("La parola non contiene doppie");
    }
    else
    {
        printf("La parola contiene doppie");
    }

    return 0;
}
