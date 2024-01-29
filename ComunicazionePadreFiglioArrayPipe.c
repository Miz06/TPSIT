#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char* argv[])
{
    int n;
    int p;
    int fd[2];
    int arr[5];
    int status;

    if (pipe(fd) == -1)
    {
        printf("Errore nel crso della pipe");
        exit(1);
    }
    else
    {
        printf("Pipe creata con successo");

        p = fork();

        if(p<0)
        {
            printf("Errore nel corso della fork");
            exit(-1);
        }
        else if(p > 0)
        {
            printf("Sono il processo padre. PID: %d - PID figlio: %d", getpid(), p);

            close(fd[1]);


            wait(&status);
        }
        else if(p == 0)
        {
            printf("Sono il processo figlio. PID: %d - PID padre: %d", getpid(), getppid());

            close(fd[0]);

            for (int i = 0; i<5; i++)
            {
                scanf("Inserire il %d° numero: %d", i+1, arr[i]);

                if(write(fd[1], arr[i], strlen(arr[i]-1)) == -1)
                {
                    printf("Errore nel corso del passaggio dei dati al padre");
                    close(fd[1]);
                    exit(2);
                }
            }

            close(fd[1]);
        }
    }
    

}