#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int p;
    int fd[2];
    int status;

    if(pipe(fd) < 0)
    {
        perror("Errore nel corso della pipe");
        exit(1);
    }

    p = fork();

    if(p > 0)
    {
        char line[255];
        FILE *FileS;
        FileS = fopen("memoryProcess.txt", "r");

        if(FileS == NULL)
        {
            perror("Errore nell'apertura del file.");
            exit(2);
        }

        close(fd[0]);

        while(fgets(line, sizeof(line), FileS) != NULL)
        {
            write(fd[1], line, sizeof(line));
        }
                            
        close(fd[1]);
        fclose(FileS);
        wait(&status);
    }
    else if(p == 0)
    {
        char line[255];
        FILE *FileD;
        FileD = fopen("FileDEstinazione.txt", "w");

        if(FileD == NULL)
        {
            perror("Errore nell'apertura del file.");
            exit(-2);
        }

        close(fd[1]);

        while(read(fd[0], line, sizeof(line)) > 0)
        {
            fprintf(FileD, "%s", line);
        }

        close(fd[0]);
        fclose(FileD);
    }
    else
    {
        perror("Errore nel corso della fork");
        exit(1);
    }

    return 0;
}