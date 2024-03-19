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
    int fd;
    studente stud1;
    
    fd = open("chiamate", O_RDONLY);
    read(fd, &stud1, sizeof(stud1));

    printf("%s\n", stud1.nome);
    printf("%s\n", stud1.cognome);
    printf("%d\n", stud1.anni);

    return 0;
}