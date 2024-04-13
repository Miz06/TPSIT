#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct{
   int numero;
   char sezione;
}class;

typedef struct{
    char nome[20];
    char cognome[20];
    float media;
    class classe;
}studente;

void* stampa (void* par){
    printf("%s\n", ((studente *)par)->nome); 
    printf("%s\n", ((studente *)par)->cognome); 
    printf("%d %c\n", ((studente *)par)->classe.numero, ((studente *)par)->classe.sezione); 
    printf("%f\n", ((studente *)par)->media); 

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

    printf("Inserire sezione della classe studente: ");
    scanf("%c", &classeStud1.sezione);

    stud1.classe = classeStud1;

    pthread_create(&t1, NULL, &stampa, (void*)&stud1);

    pthread_join(t1, NULL);

    return 0;
}