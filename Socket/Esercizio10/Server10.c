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

#define SERVERPORT 1313
#define ARR_LEN 40

void confrontaStringhe(char vett1[], char vett2[], char vett3[]){
    if(strlen(vett1)==strlen(vett2)){
        strcpy(vett3, "Stringhe della stessa lunghezza");
    }
    else if(strlen(vett1)>strlen(vett2)){
        strcpy(vett3, "Stringa 1 più lunga");
    }
    else if(strlen(vett1)<strlen(vett2)){
        strcpy(vett3, "Stringa 2 più lunga");
    }
}

int main() {
    struct sockaddr_in servizio, addr_remoto; 

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(servizio), value;
    char vett1[ARR_LEN], vett2[ARR_LEN], vett3[ARR_LEN];

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

        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);

        if (soa < 0) {
            perror("Errore nella accept");
            continue; 
        }

        if(read(soa, vett1, sizeof(vett1))<0){
            printf("Errore nella read di vett1");
            exit(EXIT_FAILURE);
            continue;
        }

        if(read(soa, vett2, sizeof(vett2))<0){
            printf("Errore nella read di vett2");
            exit(EXIT_FAILURE);
            continue;
        }

        confrontaStringhe(vett1, vett2, vett3);

        if(write(soa, vett3, sizeof(vett3))<0){
            printf("Errore nella write di vett3");
            exit(EXIT_FAILURE);
            continue;
        }
        
        close(soa);
    }

    close(socketfd);
    return 0;   
}