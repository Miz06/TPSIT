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
    int n; 

    if(argc != 4)
    {
        perror("Errore, campi necessari: [file sorgente] - [file destinazione] - [carattere da ricercare]\n");
        exit(-3);
    }
    if(pipe(fd) < 0)
    {
        perror("Errore nel corso della pipe");
        exit(1);
    }

    p = fork();

    if(p > 0)
    {
        FILE *FileS;
        FileS = fopen(argv[1], "r");

        if(FileS == NULL)
        {
            perror("Errore nell'apertura del file.");

            close(fd[0]);
            close(fd[1]);

            exit(2);
        }

        close(fd[0]);

        while((n = fread(buffer, 1, sizeof(buffer), FileS)) > 0)
        {
            write(fd[1], buffer, n);
        }
                            
        close(fd[1]);
        fclose(FileS);

        wait(&status);
    }
    else if(p == 0)
    {
        p = fork();
        
        if (p > 0)
        {
            FILE *FileD;
            FileD = fopen(argv[2], "w");
            
            if(FileD == NULL)
            {
                perror("Errore nell'apertura del file.");
                
                close(fd[0]);
                close(fd[1]);

                exit(-2);
            }

            close(fd[1]);

            while((read(fd[0], buffer, sizeof(buffer))) > 0)
            {
                fwrite(buffer, 1, sizeof(buffer), FileD);
            }

            close(fd[0]);
            fclose(FileD);
        }
        else if(p == 0)
        {
            char c;
            int contatore = 0;

            FILE *FileS;
            FileS = fopen(argv[1], "r");

            while((c = fgetc(FileS)) != EOF)
            {
                if (*argv[3] == c)
                    contatore++;
            }

            printf("Il carattere %c compare %d volte nel file.\n", *argv[3], contatore);
            fclose(FileS);
        }
        else
        {
        perror("Errore nel corso della fork");

        close(fd[0]);
        close(fd[1]);

        exit(3);
        }
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