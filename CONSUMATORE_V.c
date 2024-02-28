#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <fcntl.h>

#define LEN 2

typedef struct{
    char cognome[20];
    char nome[20];
    int anni; 
}studente;

int main(int argc, char *argv[])
{
    int fd;

    if(mkfifo("FifoName", 0777) == -1 || errno != EEXIST)
    {
        perror("Errore nella creazione della fifo");
        exit(2);
    }

    fd = open("FifoName", O_RDONLY);

    if(fd == -1)
    {
        perror("Errore nell'apertura della fifo");
        exit(1);
    }
    
    studente arr[LEN];

    read(fd, arr, sizeof(arr));

    for (int i = 0; i<LEN; i++)
    {
        printf("%d° STUDENTE\n", i+1);
        printf("Nome: %s\n", arr[i].nome);
        printf("Cognome: %s\n", arr[i].cognome);
        printf("Anni: %d\n", arr[i].anni);
    }

    close(fd);
}