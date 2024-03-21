#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <fcntl.h>

typedef struct{
    char nome[20];
    char cognome[20];
    int anni;
}studente;

int main(int argc, char *argv[])
{   
    int p, fd;
    studente stud1;
    strcpy(stud1.nome, "Beppe");
    strcpy(stud1.cognome, "Sangiorgio");
    stud1.anni = 17;

    p=fork();
    
    if(p>0)
    {
        execl("./LettoreStudente.exe", "file", NULL);
    }
    else if(p==0)
    {
        fd = open("chiamate", O_WRONLY);
        write(fd, &stud1, sizeof(stud1));
    }
    else
    {
        perror("Errore nella fork.");
        exit(1);
    }

    return 0;
}