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
        if((fd = open("FifoChat2", O_WRONLY)) == -1)
        {
            perror("Errore nell'apertura della fifo in scrittura");
            exit(1);
        }

        while(1)
        {
            scanf("%s", buffer);
            write(fd, buffer, sizeof(buffer));
        }
    }else if(p == 0)
    {
        if((fd = open("FifoChat1", O_RDONLY)) == -1)
        {
            perror("Errore nell'apertura della fifo in lettura");
            exit(-1);
        }

        while(1)
        {
            read(fd, buffer, sizeof(buffer));

            if(strcmp(buffer, "HALT\0"))
            {
                printf("Fine programma");
                close(fd);
                exit(3);
            }
            else
            {
                printf("%s\n", buffer);
            }
        }
    }
    else
    {
        perror("Errore nella creazione del figlio");
        exit(2);
    }

    return 0;
}