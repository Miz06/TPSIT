#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define DIMARRAY 5
int main(int argc, char *argv[])
{
    int p;
    int fd[2];

    p = fork();

    if(pipe(fd) < 0)
    {
        printf("Errore");
        exit(-1);
    }

    if (p > 0)
    {   
        int arr[DIMARRAY];
        int n;

        printf("Sono il processo padre. PID: %d - PID figlio: %d\n", getpid(), p);

        printf("Moltiplicare per: ");
        scanf("%d", &n);

        close(fd[1]);
        read(fd[0], arr, sizeof(int) * DIMARRAY); //la wait non viene utilizzata per la read e la write in quanto sono sincrone, bensì la utilizziamo per consentire al figlio di terminare il suo processo
        close(fd[0]);
        
        for(int i = 0; i<DIMARRAY; i++)
        {
            arr[i] = arr[i]*n;
            printf("[%d] >> %d", i, arr[i]);
        }
    }
    else if(p == 0)
    {
        int arr[DIMARRAY];
        printf("Sono il processo figlio. PID: %d - PID padre: %d\n", getpid(), getppid());

        for(int i = 0; i<DIMARRAY; i++)
        {   
            printf("Inserire il %d° numero: \n", i);
            scanf("%d", &arr[i]);
        }

        close(fd[0]);

        write(fd[1], arr, sizeof(int)*DIMARRAY);

        close(fd[1]);

    }
    else
    {
        printf("Errore");

        close(fd[0]);
        close(fd[1]);

        exit(1);
    }

}