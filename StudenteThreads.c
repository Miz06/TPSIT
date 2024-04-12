#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//NULL = (void*)0
void* stampa1 (void* par){
    printf("%s\n", (char*)par); 

    return NULL;
}

typedef struct{
   int numero;
   char sezione;
}class

typedef struct{
    char nome[20];
    char cognome[20];
    float media;
    class classe;
}studente


int main()
{
    pthread_t t1, t2;

    char* msg1 = "thread1";

    printf("Inserire nome studente: ");
    scanf()

    pthread_create(&t1, NULL, &stampa1, msg1);
    
    pthread_join(t1, NULL);

    return 0;
}