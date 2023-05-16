#include <stdio.h>
#include <string.h>
#include <limits.h>

void Funz(char *q, int lungh)
{
    for (int i = 0; i < lungh - 1; i++)
    {
        *(q + i) = *(q + i + 1);
    }
    *(q + lungh - 1) = '\0'; 
}

int main()
{
    char array[SHRT_MAX];
    char *q;
    printf("Inserire una stringa di caratteri: ");
    scanf("%s", array);
    int lunghezza = strlen(array);
    q = array; 
    Funz(q, lunghezza);

    for (int i = 0; i < lunghezza - 1; i++)
    {
        printf("%c", *(q + i));
    }

    return 0;
}