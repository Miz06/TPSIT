/*Esercizio “arrayDiPuntatori.c”
Avvalendoti del linguaggio C e utilizzando la funzione MALLOC , scrivi il codice
sorgente di un programma che:
_ crea una struttura student_ t costituita dai campi: cognome, nome, media
_ crea un array di tre puntatori a struct di tipo student_t
_ chiede all’utente di inserire i dati dei tre studenti e memorizzarli nell’array
_ stampa il contenuto delle tre strutture referenziate dall’array
_ stampa il contenuto dell’array (i tre indirizzi di memoria che puntano ai tre
studenti)
_ libera l’area di memoria occupata dalla malloc.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    typedef struct
    {
        char nome[50];
        char cognome[50];
        int media;
    } student_t;

    student_t *studentiPuntatori[3];
    
    for (int i = 0; i < 3; i++)
    {
        studentiPuntatori[i] = (student_t *)malloc(sizeof(student_t));

        printf("Inserire il nome del %d° studente:\n", i + 1);
        scanf("%s", studentiPuntatori[i]->nome);

        printf("Inserire il cognome del %d° studente:\n", i + 1);
        scanf("%s", studentiPuntatori[i]->cognome);

        printf("Inserire la media del %d° studente:\n", i + 1);
        scanf("%d", &studentiPuntatori[i]->media);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Nome del %d° studente: %s\n", i + 1, studentiPuntatori[i]->nome);
        printf("Cognome del %d° studente: %s\n", i + 1, studentiPuntatori[i]->cognome);
        printf("Media del %d° studente: %d\n", i + 1, studentiPuntatori[i]->media);
        printf("------------------------------------------\n"); 
    }

    for (int i = 0; i < 3; i++)
    {
        printf("%p\n", studentiPuntatori[i]);
        printf("%p\n", studentiPuntatori[i]->nome);
        printf("%p\n", studentiPuntatori[i]->cognome);
        printf("%p\n", studentiPuntatori[i]->media);
        printf("------------------------------------------\n"); 
    }    
    for (int i = 0; i < 3; i++)
    {
        free(studentiPuntatori[i]);
    }

    return 0;
}
