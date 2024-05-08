#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_DIM  2048
char buffer[BUFFER_DIM];
int n; 

void* leggi (void* par)
{
    n = fread(buffer,1, BUFFER_DIM, ((FILE *)par));

    return NULL;
}

void* scrivi (void* par)
{
    fwrite(buffer,1, n, ((FILE *)par));

    return NULL;
}

int main(int argc[], char *argv[])
{
    pthread_t t1, t2;

    FILE *sorgente;
    FILE *destinazione;

    sorgente = fopen(argv[1], "r");
    if(sorgente == NULL)
    {
        printf("Errore nell'apertura del file sorgente");
        return 1; 
    }

    destinazione = fopen(argv[2], "w");
    if(destinazione == NULL)
    {
        printf("Errore nell'apertura del file destinazione");
        return 2; 
    }

    pthread_create(&t1, NULL, &leggi, (void*)&argv[1]);
    pthread_create(&t2, NULL, &scrivi, (void*)&argv[2]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    fclose(sorgente);
    fclose(destinazione);

    return 0;
}