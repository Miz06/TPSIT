#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    printf("ciao");
    printf("Quanti parametri: %d\n", argc);

    for(int i = 0; i<argc; i++)
    {
        printf("%s\n , argcv[i]"); 
    }

    return 0;  
}

    //gcc nomefile.c -o nomefile.exe
    //./nomefile.exe