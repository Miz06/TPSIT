#include <stdlib.h>
#include <stdio.h>
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
    int p, fd[2], status;

    pipe(fd);
    p=fork();
    studente stud1;
    
    if(p>0)
    {
        wait(&status);
        printf("%s\n", stud1.nome);
        printf("%s\n", stud1.cognome);
        printf("%d\n", stud1.anni);
    }
    else if(p==0)
    {
        fd[0] = open("FifoStudente", O_RDONLY);
        read(fd[0], &stud1, sizeof(stud1));
        close(fd[0]);
    }
    else
    {
        perror("Errore nella fork.");

    }

    return 0;
}