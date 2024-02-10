#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

#define MAX 30

typedef struct{
    char titolo[MAX];
    char autore[MAX];
    float prezzo;
}libro;


int main(int argc, char *argv[])
{
    int p, status;
    int fd[2];
    libro l;

    if(pipe(fd) < 0)
    {
        perror("Errore nel corso della creazione della pipe.");
        exit(1);
    }

    p = fork();

    if(p > 0)
    {
        strcpy(l.titolo, "Libro1");
        strcpy(l.autore, "Autore1");
        l.prezzo = 4.99;

        close(fd[0]);
        write(fd[1], l.titolo, sizeof(l.titolo));
        write(fd[1], l.autore, sizeof(l.autore));
        write(fd[1], &l.prezzo, sizeof(l.prezzo));
        close(fd[1]);

        wait(&status);
    }
    else if(p == 0)
    {
        libro l;

        close(fd[1]);
        read(fd[0], l.titolo, sizeof(l.titolo));
        read(fd[0], l.autore, sizeof(l.autore));
        read(fd[0], &l.prezzo, sizeof(l.prezzo));
        close(fd[0]);

        printf("Titolo: %s\n", l.titolo);
        printf("Autore: %s\n", l.autore);
        printf("Prezzo: %f\n", l.prezzo);

    }
    else
    {
        perror("Errore nel corso della creazione della fork.");
    }
    return 0;
}