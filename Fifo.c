#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
    //Dichiarazione variabili
    int fd;
    //int x; non va dichiarata qui perchè dichiarazione e inizializzazione vanno fatte dopo la creazione della pipe

    //Creazione FIFO
    if(mkfifo("MyFifo1", 0777) == -1) //proprietario, gruppo a cui appartiene il proprietario, tutti gli altri utenti => (tutti i permessi a tutti)     
    {//lo 0 viene messo davanti non per non dare permessi bensì perchè se non lo si mette il programma da errore 
        if(errno != EEXIST)
        {
            perror("Errore nella creazione della FIFO");
            exit(1);
        }
    }          

    //Apro la FIFO in scrittura

    int x = 90;
    fd = open("MyFifo1", O_WRONLY); //fd == 1 in quanto la FIFO è aperta in scrittura
    printf("FIFO aperta");

    if(write(fd, &x, sizeof(x)) == -1)
    {
        perror("Errore nella creazione della FIFO");
        exit(2);
    }
    printf("Ho scritto nella FIFO");
    close(fd);
    
    
    return 0;
}
