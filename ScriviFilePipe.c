#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define DIM_BUFFER 1048
int main(int argc, char *argv[])
{
    char buffer[DIM_BUFFER];
    int p, status;
    int fd[2];

    if(pipe(fd) < 0)
    {
        perror("Errore nel corso della pipe");
        exit(1);
    }

    p = fork();

    if(p > 0)
    {
        FILE *FileS;
        FileS = fopen("memoryProcess.txt", "r");

        if(FileS == NULL)
        {
            perror("Errore nell'apertura del file.");

            close(fd[0]);
            close(fd[1]);

            exit(2);
        }

        close(fd[0]);

        while(fgets(buffer, sizeof(buffer), FileS) != NULL)
        {
            write(fd[1], buffer, sizeof(buffer));
        }
                            
        close(fd[1]);
        fclose(FileS);

        wait(&status);
    }
    else if(p == 0)
    {
        FILE *FileD;
        FileD = fopen("FileDestinazione.txt", "w");
        
        if(FileD == NULL)
        {
            perror("Errore nell'apertura del file.");
            
            close(fd[0]);
            close(fd[1]);

            exit(-2);
        }

        close(fd[1]);

        while(read(fd[0], buffer, sizeof(buffer)) > 0)
        {
            fprintf(FileD, "%s", buffer);
        }

        close(fd[0]);
        fclose(FileD);
    }
    else
    {
        perror("Errore nel corso della fork");

        close(fd[0]);
        close(fd[1]);

        exit(1);
    }

    return 0;
}