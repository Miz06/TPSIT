#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct{
    int numero;
    int array[1000];
}parametri;

void* find1 (void* par)
{
    for(int i = 0; i<250; i++)
    {
        if((((parametri*)par)->array)[i] == ((parametri*)par)->numero)
            printf("\nIl numero %d si trova nella posizione %d\n", ((parametri*)par)->numero, i);
    }

    return NULL;
}

void* find2 (void* par)
{
    for(int i = 250; i<500; i++)
    {
        if((((parametri*)par)->array)[i] == ((parametri*)par)->numero)
            printf("\nIl numero %d si trova nella posizione %d\n", ((parametri*)par)->numero, i);
    }

    return NULL;
}

void* find3 (void* par)
{
    for(int i = 500; i<750; i++)
    {
        if((((parametri*)par)->array)[i] == ((parametri*)par)->numero)
            printf("\nIl numero %d si trova nella posizione %d\n", ((parametri*)par)->numero, i);
    }

    return NULL;
}

void* find4 (void* par)
{
    for(int i = 750; i<1000; i++)
    {
        if((((parametri*)par)->array)[i] == ((parametri*)par)->numero)
            printf("\nIl numero %d si trova nella posizione %d\n", ((parametri*)par)->numero, i);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    parametri p;
    srand(time(NULL));//inizializza il random
    pthread_t t1, t2, t3, t4;

    for(int i = 0; i<1000; i++)
    {
        p.array[i] = rand()%500; //uso la funzione random per generare numeri casuali
    }

    FILE *f;
    f = fopen("fileT1000.txt", "w");

    for(int i = 0; i<1000; i++)
    {
        fprintf(f, "%d", p.array[i]);
        fprintf(f, "%s", "\n");
    }

    fclose(f);
    printf("Inserire il numero che si desidera cercare nell'array: ");
    scanf("%d", &(p.numero));

    pthread_create(&t1, NULL, &find1, (void*)&p);
    pthread_create(&t2, NULL, &find2, (void*)&p);
    pthread_create(&t3, NULL, &find3, (void*)&p);
    pthread_create(&t4, NULL, &find4, (void*)&p);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    return 0;
}