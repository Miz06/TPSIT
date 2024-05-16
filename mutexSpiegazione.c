#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLICE_DIM 64
#define NUM_SLICES 16

int write_index, read_index, n_slices;
pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;

typedef struct{
    unsigned char bufferInStruc[SLICE_DIM]; //byte di una slice
    int n; //numero di byte letti (che è sempre 64 spesso tranne l'ultimo blocco di byte letti)
}bufferStruct;

bufferStruct buffer[NUM_SLICES]; //buffer di 15 slices di grandezza 64 byte

void* writeFile(void* arg){
    pthread_mutex_lock(&mutex); //per proteggere la sezione critica dall'accesso di altri thread oltre a quello corrente

    while(n_slices<=0)
        pthread_cond_wait(&not_empty, &mutex);
        
    if(n_slices>0)
    {
        fwrite(buffer[read_index].bufferInStruc, 1, buffer[write_index].n, (FILE *)arg);
        read_index = (read_index+1) % NUM_SLICES;
        n_slices--;

        pthread_cond_signal(&not_full); //per "svegliare" il thread "addormentato"
    }
    
    pthread_mutex_unlock(&mutex);//per sbloccare la sezione critica occupata dal thread
}

void* readFile(void* arg){
    int n;

    pthread_mutex_lock(&mutex);

    while(n_slices>=NUM_SLICES)
        pthread_cond_wait(&not_full, &mutex); //per "addormentare" il thread 

    n = fread(buffer[write_index].bufferInStruc, 1, SLICE_DIM, (FILE *)arg);

    if(n>0)
    {
        buffer[write_index].n = n;
        write_index = (write_index+1) % NUM_SLICES;
        n_slices++;
        pthread_cond_signal(&not_empty);
    }

    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t writeTh, readTh;

    FILE *fr, *fw;
    fr = fopen("origine", "rb");
    fw = fopen("destinazione", "wb");

    pthread_create(&writeTh,NULL, &writeFile, NULL);
    pthread_create(&readTh,NULL, &readFile, NULL);

    //se due thread accedono alla stessa zona di memoria l'esito è impredicibile, quindi bisogna farvi accedere solamente un thread alla volta


    return 0;
}