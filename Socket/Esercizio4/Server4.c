//SERVER
#include <stdio.h>       //std in-out
#include <stdlib.h>      //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h>  //funz. accept+bind+listen
#include <sys/types.h>   //funz. accept
#include <netinet/in.h>  //definiscono la struttura degli indirizzi 
#include <string.h>      //funz. stringhe
#include <errno.h>       //gestioni errori connessione
#include <ctype.h>       //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX
#include <ctype.h>

#define DIM 50
#define SERVERPORT 1313

int carattereInStr(char str[], char c){
    int count = 0;

    for(int i = 0; i<strlen(str); i++){
        if(str[i] == c){
            count++;
        }
    }

    return count;
}

int main() {
    struct sockaddr_in servizio, addr_remoto; 

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(servizio), num;
    char str[DIM], c;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore nel bind");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    if (listen(socketfd, 10) < 0) {
        perror("Errore nel listen");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // ciclo infinito
    for (; ;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);

        soa=accept(socketfd,(struct sockaddr*)&addr_remoto,&fromlen);
        
        if(read(soa,str,sizeof(str))<0){
            printf("Errore nella read della stringa");
            close(soa);
            continue;
        }

        printf("\nStringa ricevuta: %s\n", str);

        if(read(soa, &c, sizeof(c))<0){
            printf("Errore nella read del carattere");
            close(soa);
            continue;
        }

        printf("Carattere ricevuto: %c", c);

        num = carattereInStr(str, c);

        if(send(soa, &num, sizeof(int), 0)<0){
            printf("Errore nella send di num");
            close(soa);
            continue;
        }

        close(soa);
    }

    close(socketfd);
    return 0;   
}