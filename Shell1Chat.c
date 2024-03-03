#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <fcntl.h>

#define MESSAGE_MAX_LEN 1024
int main(int argc, char *argv[])
{//nome fifo = Chat
    int fd, p, status;
    char buffer[MESSAGE_MAX_LEN];
    
    p = fork();

    if(p>0)
    {
        wait(&status);

        if((fd = open("Chat", O_WRONLY)) == -1)
        {
            perror("Errore nell'apertura della fifo in scrittura");
            exit(1);
        }

        scanf("\n%s", buffer);
        write(fd, buffer, sizeof(buffer));

        close(fd);

    }else if(p == 0)
    {
        if((fd = open("Chat", O_RDONLY)) == -1)
        {
            perror("Errore nell'apertura della fifo in lettura");
            exit(-1);
        }

        read(fd, buffer, sizeof(buffer));
        printf("%s", buffer);

        close(fd);
    }
    else
    {
        perror("Errore nella creazione del figlio");
        exit(2);
    }

    return 0;
}