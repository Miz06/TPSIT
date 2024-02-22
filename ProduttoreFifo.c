#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;//fd è il file descriptor (handle)

    //la fifo una volta creata da terminale (mkfifo nome_fifo) non va più creata
    //=> risulta un errore crearla ad ogni utilizzo del codice

    int numbers[5];

    fd = open("sum", O_WRONLY);

    if(fd == -1)
    {
        perror("Errore nell'apertura della fifo.");
        close(fd);
        exit(1);
    }

    for (int i = 0; i<5; i++)
    {
        numbers[i] = rand() % 100;
    }
    
    write(fd, numbers, sizeof(numbers));
    close(fd);

}