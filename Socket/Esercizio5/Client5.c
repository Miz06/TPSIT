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
#include <arpa/inet.h>  //per conversione degli indirizzi di rete

#define DIM 50
#define SERVERPORT 1313

int main(int argc,char** argv)
{   
    struct sockaddr_in servizio, addr_remoto; //INDIRIZZO IP - PORTA - DOMINIO 

    //inizializzazione dell'elemento di tipo sockaddr
    servizio.sin_family=AF_INET; 
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port=htons(SERVERPORT); 

    char str[DIM];
    int socketfd, fromlen=sizeof(servizio), value;

    socketfd = socket(AF_INET, SOCK_STREAM, 0); 

    const char* ip_server = "192.168.2.204"; // Indirizzo IP del server

    if (inet_pton(AF_INET, ip_server, &servizio.sin_addr) <= 0) {
        perror("Errore nella conversione dell'indirizzo IP");
        exit(EXIT_FAILURE);
    }

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

    if(write(socketfd, str, sizeof(str))<0){
        printf("Errore nella write di str");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("\nIn attesa di risposta dal server...\n");
    fflush(stdout);
        
    if(read(socketfd, str, sizeof(str))<0){
        printf("Errore nella read della stringa");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("Stringa ordinata: %s\n", str);

    close(socketfd);
    return 0;
}
