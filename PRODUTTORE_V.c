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

    fd = open("FifoName", O_WRONLY);

    if(fd == -1)
    {
        perror("Errore nell'apertura della fifo");
        exit(1);
    }

    studente arr[LEN];

    strcpy(arr[0].nome, "Alessandro");
    strcpy(arr[1].nome, "Luca");

    strcpy(arr[0].cognome, "Mizzon");
    strcpy(arr[1].cognome, "Buttini");

    arr[0].anni = 17;
    arr[1].anni = 18;

    write(fd, arr, sizeof(arr));

    close(fd);
}