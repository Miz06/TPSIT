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
    int p, fd, status;
    FILE *fileOrigine;

    if((fileOrigine = fopen(argv[1], "w")) == NULL)
    {
        perror("Error");
        exit(1);
    }

    atleta a1;
    a1.anni = 17;
    strcpy(a1.nome, "Alessandro");
    a1.peso = 80;

    fprintf(fileOrigine, "%d %s %f", a1.anni, a1.nome, a1.peso);

    mkfifo("review", 0777);
    fd = open("review", O_WRONLY);
    write(fd, &a1, sizeof(a1));
    close(fd);
    
    return 0;
}