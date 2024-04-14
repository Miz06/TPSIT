#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* cerca1 (void* array)
{
    for(int i = 0; i<5; i++)
    {
        if(((int*)array)[i] == 8)
            printf("Il numero 8 si trova nella posizione %d", i);
    }

    return NULL;
}

void* cerca2 (void* array)
{
    for(int i = 0; i<10; i++)
    {
        if(((int*)array)[i] == 8)
            printf("Il numero 8 si trova nella posizione %d\n", i);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int arr[10];
    srand(time(NULL));//inizializza il random

    for(int i = 0; i<10; i++)
    {
        arr[i] = rand(); //uso la funzione random per generare numeri casuali
    }

    arr[6] = 8;

    cerca1((void*)&arr);
    cerca2((void*)&arr);
    
    return 0;
}