#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define DIMARRAY 5
int main(int argc, char *argv[])
{
    int p;
    int fd[2];
    int status;

    if(pipe(fd) < 0)
    {
        printf("Errore");
        exit(-1);
    }
    
    p = fork();

    if (p > 0)
    {   
        int arr[DIMARRAY];
        int n;

        printf("Sono il processo padre. PID: %d - PID figlio: %d\n", getpid(), p);

        close(fd[1]);
        read(fd[0], arr, sizeof(int) * DIMARRAY);
        close(fd[0]);

        printf("Moltiplicare per: ");
        scanf("%d", &n);

        for(int i = 0; i<DIMARRAY; i++)
        {
            arr[i] = arr[i]*n;
            printf("[%d] >> %d", i, arr[i]);
        }

        wait(&status);
    }
    else if(p == 0)
    {
        int arr[DIMARRAY];
        printf("Sono il processo figlio. PID: %d - PID padre: %d\n", getpid(), getppid());

        for(int i = 0; i<DIMARRAY; i++)
        {   
            printf("Inserire il %d° numero: ", i);
            scanf("%d", &arr[i]);
        }

        close(fd[0]);
        write(fd[1], arr, sizeof(int)*DIMARRAY);
        close(fd[1]);
    }
    else
    {
        printf("Errore");
        exit(1);
    }

}