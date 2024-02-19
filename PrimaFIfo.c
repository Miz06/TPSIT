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

    if (mkfifo("Fifo", 0777) == -1)
    {
        if(errno != EEXIST)
        {
            perror("Errore nella creazione della fifo.");
            exit(1);
        }
    }

    srand(time(NULL));
    int numbers[5];

//////////////////////////

    fd = open("Fifo", O_WRONLY);

    for (int i = 0; i<5; i++)
    {
        numbers[i] = rand() % 99 +1;
    }
    
    write(fd, &numbers, sizeof(numbers));
    close(fd);

//////////////////////
    fd = open("Fifo", O_RDONLY);

    read(fd, &numbers, sizeof(numbers));

    for(int i = 0; i<5; i++)
    {
        printf("numero %d: %d\n", i, numbers[i]);
    }

    close(fd);

}