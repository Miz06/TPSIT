//CLIENT
#include <stdio.h>       //std in-out
#include <stdlib.h>      //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h>  //funz. accept+bind+listen
#include <sys/types.h>   //funz. accept
#include <netinet/in.h>  //definiscono la struttura degli indirizzi
#include <string.h>      //funz. stringhe
#include <errno.h>       //gestioni errori connessione
#include <ctype.h>       //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313

int main(int argc,char** argv)
{   
    struct sockaddr_in servizio, addr_remoto; //INDIRIZZO IP - PORTA - DOMINIO 

    //inizializzazione dell'elemento di tipo sockaddr
    servizio.sin_family=AF_INET; 
    servizio.sin_addr.s_addr=htonl(INADDR_ANY); 
    servizio.sin_port=htons(SERVERPORT); 

    char str[DIM], c;
    int socketfd, soa, fromlen=sizeof(servizio), value;

    socketfd = socket(AF_INET, SOCK_STREAM, 0); 

    if (socketfd < 0) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    if (connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore nella connessione al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("Inserisci la stringa: ");
    scanf("%s",str);

    printf("Inserisci il carattere: ");
    scanf(" %c", &c);

    write(socketfd, str, sizeof(str));
    write(socketfd, &c, sizeof(c));

    printf("\nIn attesa di risposta dal server...\n");
    fflush(stdout);
        
    recv(socketfd, &value, sizeof(int), 0);

    printf("Il carattere %c si ripete %d volte nella stringa %s\n", c, value, str);

    close(socketfd);
    return 0;
}
