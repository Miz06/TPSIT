#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//Threads
//POSIX -> Operativ System 

//NULL = (void*)0
void* stampa1 (void* par){
    printf("%s\n", (char*)par); 

    return NULL;
}

void* stampa2 (void* par){
    printf("%s\n", (char*)par); 

    return NULL;
}

void* stampa3 (void* par){
    printf("%s\n", (char*)par); 

    return NULL;
}

int main()
{//faccio eseguire in parallelo 4 istruzioni tramite i thread
//Il processo (thread principale) genera i thread e li lancia 

    pthread_t t1, t2, t3;

    char* msg1 = "thread1";
    char* msg2 = "thread2";
    char* msg3 = "thread3";
    
    printf("da programma (thread principale)\n");

    pthread_create(&t1, NULL, &stampa1, msg1);
        pthread_create(&t2, NULL, &stampa2, msg2);
            pthread_create(&t3, NULL, &stampa3, msg3);

    pthread_join(t1, NULL);
        pthread_join(t2, NULL);
            pthread_join(t3, NULL);

    //printf("thread1\n");
    //printf("thread2\n");
    //printf("thread3\n");

    return 0;
}