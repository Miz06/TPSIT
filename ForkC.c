#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int p;

int main()
{
    printf("ciao\n");//viene stampato ciao una sola volta in quantto il codice viene diviso in due processi 
                    //solamente dopo aver eseguito il fork
    //int p; //Se dichiaro p all'interno del main noto che il PID del processo padre del figlio cambia
            //in quanto ora p ha visibilità solo all'interno del main quindi i due processi non possono più condividere lo stesso spazio di memoria 
    p = fork();

    if(p>0)
    {
        printf("Sono il processo padre. PID: %d Padre:%d\n", getpid(), getppid());
    }
    else
    {
        printf("Sono il processo figlio. PID: %d Padre:%d\n", getpid(), getppid());

    }

    //si può notare che il PID padre del figlio è uguale al PID del padre nonchè il processo padre 
    return 0;
}