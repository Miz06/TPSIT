#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define BUFFER_SIZE 1024
/*OBIETTIVO: far comunicare padre e figlio attraverso una pipe ossia
             il padre scive un messaggio nella pipe e
			 il figlio lo legge dalla pipe*/


int main()
{
	//dichiarazione var
	int p;
	int fd[2];
	//char buffer[BUFFER_SIZE];
	int n;
	int status;
	if(pipe(fd) == -1) //N.B. La pipe e' SINCRONA !!!
	{
		printf("\nErrore creazione pipe");
		exit(-1); //esco dal prg
	}

	p=fork(); //padre genera figlio
	if (p<0)
	{
		printf("\nErrore generazione figlio");
	}

	if(p>0) //padre
	{
		printf("\nSono il padre: il mio PID=%d, mio figlio ha PID=%d\n", getpid(), p);
		close(fd[0]); //padre chiude pipe in lettura (output pipe)
		
		const char* messaggio="Buona fortuna\n";
		if( write(fd[1], messaggio,  strlen(messaggio)) == -1)
		{
			printf("\nErrore di scrittura nella pipe");
			close(fd[1]); //bisogna sempre chiudere il fd
			exit(-1);
		}
		close(fd[1]);
		wait(&status); /*padre attende la terminazione figlio 
		                 altrimenti rimarrebbe un figlio zombie*/
	}
	else //figlio
	{
		char buffer[BUFFER_SIZE];

		printf("\nSono il figlio: il mio PID=%d, mio padre ha PID=%d\n", getpid(), getppid());
		close(fd[1]);
		n=read(fd[0], buffer, BUFFER_SIZE);
		if(n==-1)
		{
			printf("\nErrore nella lettura della pipe");
			close(fd[0]); //bisogna sempre chiudere il fd
			exit(-1);
		}
		else 
		{
			buffer[n]='\0';	
			printf("\nMessaggio letto: %s", buffer);
			close(fd[0]);
		}
	}

	return 0;
}
=======
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
