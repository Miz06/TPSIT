#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//struct classe (in quanto la classe è composta da numero e sezione)
typedef struct{
   int numero;
   char sezione;
}class;

//struct studente
typedef struct{
    char nome[20];
    char cognome[20];
    float media;
    class classe;
}studente;

//funzione che stampa i dati dello studente su file
void* scriviSuFile (void* par){
    //scrittura
    
    printf("\n^^^^^^^^^^^^^^^^^^^^\n");
    printf("Scrittura su file terminata");
 
    return NULL;
}

//funzione che stampa i dati di uno studente
void* stampa (void* par){
    printf("\n^^^^^^^^^^^^^^^^^^^^\n");
    printf("Nome: %s\n", ((studente *)par)->nome); 
    printf("Cognome: %s\n", ((studente *)par)->cognome); 
    printf("Classe: %d%c\n", ((studente *)par)->classe.numero, ((studente *)par)->classe.sezione); 
    printf("Media: %f\n", ((studente *)par)->media); 

    return NULL;
}

int main()
{
    pthread_t t1;

    studente stud1; 
    class classeStud1;

    printf("Inserire nome studente: ");
    scanf("%s", stud1.nome);

    printf("Inserire cognome studente: ");
    scanf("%s", stud1.cognome);

    printf("Inserire media studente: ");
    scanf("%f", &stud1.media);

    printf("Inserire numero della classe studente: ");
    scanf("%d", &classeStud1.numero);

    printf("Inserire sezione della classe studente:");
    scanf(" %c", &classeStud1.sezione);
    
    //assegno allo studente la classe
    stud1.classe = classeStud1;

    pthread_create(&t1, NULL, &stampa, (void*)&stud1);
    pthread_join(t1, NULL);

    return 0;
}