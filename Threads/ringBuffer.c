#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_DIM 2048 //grandezza di un singolo buffer (nonchè elemeno dell'array di buffer)
#define SLICES 64 //numero di elementi dell'array di buffer

FILE *source;
FILE *destination;

int write_index = 0; 
int read_index = 0; 
int N_BLOCK = 0; 

bool end = false;

pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;

typedef struct //struct che rappresenta un singolo buffer
{
	int buff[BUFFER_DIM];
	int n;
}buffer;

buffer ring_buffer[SLICES]; //array di buffer

void *readFile(void *arg)
{
	pthread_mutex_lock(&mutex); //quando il thread è in esecuzione nessun'altro thread può accedere alle sue stesse risorse

	int n;

	while(N_BLOCK>=SLICES)
	{
		pthread_cond_wait(&not_empty, &mutex); //il thread viene "messu in pausa"
	}

	while (!feof((FILE *)arg))
	{
		n = fread(ring_buffer[write_index].buff, 1, BUFFER_DIM, source); /*scrivo nel buffer in posizione write_index 
		il contenuto del file */

		if(n>0) //se il file non era vuoto...
		{
			ring_buffer[write_index].n = n; //attribuisco a n del buffer i caratteri letti (n)
			write_index = (write_index)%SLICES; //nel momento in cui si arriva all'ultimo elemento si riparte da capo
			N_BLOCK++;  //incremento il numero di elementi pieni

			pthread_cond_signal(&not_full); //faccio "ripartire" il thread
		}
	}

 end = true;

	pthread_mutex_unlock(&mutex); //rendo le risorse in uso dal thread nuovamente disponibili
}

void *writeFile(void *arg)
{
	pthread_mutex_lock(&mutex); //quando il thread è in esecuzione nessun'altro thread può accedere alle sue stesse risorse

	while(N_BLOCK<=0) //finchè non ho nessun elemento dell'array da scrivere nel file non scrivo
	{
		pthread_cond_wait(&not_full, &mutex); //il thread viene "messu in pausa"
	}

	while(!end || N_BLOCK > 0)
	{
		fwrite(ring_buffer[read_index].buff, 1, BUFFER_DIM, destination); //scrittura su file
		read_index = (read_index)%SLICES; //ragionamento analogo al precedente
		N_BLOCK--; //diminuisco elementi occupati

		pthread_cond_signal(&not_empty); //"risvegliato" il thread
	}

	pthread_mutex_unlock(&mutex); //rendo le risorse in uso dal thread nuovamente disponibili
}


int main(int argc, char *argv[])
{	
	pthread_t t1, t2;

	source = fopen(argv[1], "r");
	
	if(source == NULL)
	{
		perror("Errore nell'apertura del file sorgente");
		return 1;
	}

	destination = fopen(argv[2], "a");

	if(destination == NULL)
	{
		perror("Errore nell'apertura del file destinazione");
		return 2;
	}
	
	pthread_create(&t1, NULL, &readFile, (void *)source);
	pthread_create(&t2, NULL, &writeFile, (void *)destination);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
