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
    int fd;
    
        /*
    if (mkfifo("sum", 0777) == -1)
    {
        if(errno != EEXIST)
        {
            perror("Errore nella creazione della fifo.");
            exit(1);
        }
    }
    */
   
    int numbers[5];
    int somma = 0;

    fd = open("sum", O_RDONLY);

    read(fd, &numbers, sizeof(numbers));

    for(int i = 0; i<5; i++)
    {
        somma += numbers[i];
    }

    printf("Somma: %d", somma);
    close(fd);

}