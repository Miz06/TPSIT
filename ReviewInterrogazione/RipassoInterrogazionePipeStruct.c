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
    double peso;
    char nome[20];
    int anni;
}atleta;

int main (int argc, char *argv[])
{
    int p, fd[2], status;
    atleta a1;

    if(pipe(fd)<0)
    {
        perror("Errore");
        exit(1);
    }

    p = fork();

    if(p>0)
    { 
        printf("padre - pid: %d - pid figlio: %d\n", getpid(), p);
        a1.anni = 17;
        strcpy(a1.nome, "Alessandro");
        a1.peso = 80;

        close(fd[0]);
        write(fd[1], &a1, sizeof(a1));
        close(fd[1]);

        wait(&status);
    }
    else if (p==0)
    {
        printf("figlio - pid: %d - pid padre: %d\n", getpid(), getppid());

        close(fd[1]);
        read(fd[0], &a1, sizeof(a1));
        close(fd[0]);
    
        printf("Anni: %d - Nome: %s - Peso: %f\n", a1.anni, a1.nome, a1.peso);
    }
    else
    {
        perror("Errore");
        exit(2);
    }

    ///////////////////////////////////////////
    
    return 0;
}