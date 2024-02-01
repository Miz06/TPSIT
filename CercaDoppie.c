#include <stdio.h>
#include <string.h>
int main() //Alessandro Mizzon 
{
    char parola[100]; 
    int i = 1; 
    bool doppia = false; 

    printf("Inserire una parola: ");
    scanf("%s", parola);

    do
    {
        if (parola[i] == parola[i - 1])
        {
            doppia = false;
        }
        i++;
    } while (i < 100 && doppia == false);

    if (doppia == false)
    {
        printf("La parola non contiene doppie");
    }
    else
    {
        printf("La parola contiene doppie");
    }

    return 0;
}
