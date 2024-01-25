#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int p;
int fd[2];
#define BUFFER_SIZE 1024

int main()
{
    //f[0] read >> ciò che esce dalla pipe
    //f[1] write >> ciò che entra nella pipe
    
    if(pipe[fd] == -1)
        printf("Errore nella creazione della pipe");
    else
    {
        p = fork();

        if(p>0)
        {
            printf("Sono padre. PID: %d - PID figlio: %d", getpid(), p);ù
            close(fd[0]);

            const char* messaggio = "Good luck";
            if(write(fd[1], messaggio, strlen(messaggio)) == -1)
            {
                printf("\nErrore nella scrittura della pipe");
                close(fd[1]);
                exit(-1);
            }
            close(f[1]);
        }
        
        else if(p==0)
        {
            printf("Sono figlio. PID: %d - PID padre: %d", getpid(), getppid());
            close(fd[0]);
            read(fd[0], buffer, BUFFER_SIZE);
        
            if(n == -1)
            {
                printf("\nErrore nella lettura della pipe")
                close(fd[0]);
                exit(-1);
            }
            else
            {
                buffer[n] ='0';
                

            }
        }
        else
            print("Errore nel corso della fork.");
            exit(2);
    }
    return 0;
}