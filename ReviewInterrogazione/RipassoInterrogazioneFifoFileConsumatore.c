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

#define MAX 1024
int main (int argc, char *argv[])
{
    int p, fd, status, n;
    atleta a1;
    FILE *fileDestinazione;
    char buffer[10];

    if((fileDestinazione = fopen(argv[1], "r")) == NULL)
    {
        perror("Error");
        exit(1);
    }

    fscanf(fileDestinazione, "%s", buffer);
    printf("%s", buffer);
    
    fd = open("review", O_RDONLY);
    read(fd, &a1, sizeof(a1));
    printf("Nome: %s - Anni: %d - Peso: %f\n", a1.nome, a1.anni, a1.peso);
    close(fd);

    return 0;
}