#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char titolo[30];
    char autore[30];
    float prezzo;
}libro;


int main(int argc, char *argv[])
{
    int p, status;
    int fd[2];
    libro l[2];

    if(pipe(fd) < 0)
    {
        perror("Errore nel corso della creazione della pipe.");
        exit(1);
    }

    p = fork();

    if(p > 0)
    {
        strcpy(l[0].titolo, "Libro1");
        strcpy(l[0].autore, "Autore1");
        l[0].prezzo = 4.99;

        strcpy(l[1].titolo, "Libro2");
        strcpy(l[1].autore, "Autore2");
        l[1].prezzo = 8.99;

        close(fd[0]);

        for(int i = 0; i<2; i++) 
        {
        write(fd[1], l[i].autore, sizeof(l[i].autore));      
        write(fd[1], l[i].autore, sizeof(l[i].autore));
        write(fd[1], &l[i].prezzo, sizeof(l[i].prezzo));
        } 

        close(fd[1]);

        wait(&status);
    }
    else if(p == 0)
    {
        libro l;

        close(fd[1]);

        for(int i = 0; i<2; i++) 
        {
        read(fd[0], l[i].autore, sizeof(l[i].autore));      
        read(fd[0], l[i].autore, sizeof(l[i].autore));
        read(fd[0], &l[i].prezzo, sizeof(l[i].prezzo));
        }

        close(fd[0]);

        for(int i = 0; i<2; i++) 
        {
        printf("Titolo: %s\n", l[i].titolo);
        printf("Autore: %s\n", l[i].autore);
        printf("Prezzo: %f\n", l[i].prezzo);
        } 

    }
    else
    {
        perror("Errore nel corso della creazione della fork.");
    }
    return 0;
}