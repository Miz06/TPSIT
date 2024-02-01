#include <stdlib.h>
#include <unist.h>
#include <sys/wait>
#include <stdio.h>


int main(int argc, char *argv[])
{
    int p;
    int fd[2]:


    p = fork();

    if (p > 0)
    {
        printf("Sono il processo padre. PID: %d - PID figlio: %d" getpid(), p);
    }
    else if(p == 0)
    {
        pritf("Sono il processo figlio. PID: %d - PID padre: %d", getpid(), getppid());

    }
    else
    {
        printf("Errore");
        exit(1);
    }

}