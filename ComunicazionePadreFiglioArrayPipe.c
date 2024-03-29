#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define l 5
int main(int argc, char* argv[])
{
    int n;
    int p;
    int fd[2];
    int arr[l];
    int status;

    if (pipe(fd) == -1)
    {
        perror("Errore nel crso della pipe");
        exit(1);
    }
    else
    {
        printf("Pipe creata con successo\n");

        p = fork();

        if(p<0)
        {
            perror("Errore nel corso della fork");
            exit(-1);
        }
        else if(p > 0)
        {
            printf("Sono il processo padre. PID: %d - PID figlio: %d\n", getpid(), p);
            close(fd[1]);

            int arr2[l];
            read(fd[0], arr2, sizeof(arr2));
            close(fd[0]);

            int n;
            printf("Per quanto moltiplicare gli elementi dell'array? ");
            scanf("%d", &n);

            for (int i = 0; i<l; i++)
            {
                arr2[i] = arr2[i]*n;
                printf("[%d] >> %d\n", i, arr2[i]);
            }
            
            wait(&status);
        }
        else if(p == 0)
        {
            printf("Sono il processo figlio. PID: %d - PID padre: %d\n", getpid(), getppid());
            close(fd[0]);

            for (int i = 0; i<5; i++)
            {
                printf("\nInserire il %d° numero: ", i+1);
                scanf("%d", &arr[i]);
            }

            if(write(fd[1], arr, sizeof(arr)) == -1)
                {
                    perror("Errore nel corso del passaggio dei dati al padre");
                    close(fd[1]);
                    exit(2);
                }

            close(fd[1]);
        }
    }
}