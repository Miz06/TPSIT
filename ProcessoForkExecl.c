#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

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
        fd[0] = open("FifoStudente", O_RDONLY);
        read(fd, &stud1, sizeof(stud1));
        close(fd);

        execl("LettoreStudente.exe", NULL);
    }
    else if(p==0)
    {
        strcpy(stud1.nome, "Alessandro");
        strcpy(stud1.cognome, "Mizzon");
        stud1.anni = 17;
    }
    else
    {
        perror("Errore nella fork.");

    }




    return 0;
}