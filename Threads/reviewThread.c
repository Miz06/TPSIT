#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int arr[100];
    int num;
}par;

void* cerca1(void *arg){
    for(int i = 0; i<50; i++)
    {
        if(((par *)arg)->arr[i] == ((par *)arg)->num)
        {
            printf("Numero trovato in posizione: %d\n", i);
        }
    }
}

void* cerca2(void *arg){
    for(int i = 50; i<100; i++)
    {
        if(((par *)arg)->arr[i] == ((par *)arg)->num)
        {
            printf("Numero trovato in posizione: %d\n", i);
        }
    }
}

int main(int argc[], char *argv[])
{
    pthread_t t1, t2;
    par P;

    FILE *file;
    file = fopen(argv[1], "a");

    if(file == NULL)
    {
        perror("Errore nell'apertura del file");
        return 1;
    }

    for(int i = 0; i<100; i++)
    {
        P.arr[i] = rand() % 100;
        fprintf(file, "%d\n", P.arr[i]);
    }

    P.num = atoi(argv[2]);

    pthread_create(&t1, NULL, &cerca1, (void *)&P);
    pthread_create(&t2, NULL, &cerca2, (void *)&P);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}