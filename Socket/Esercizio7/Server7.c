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
#define ARR_LEN 3

//il parametro n serve a non dover utilizzare una funzione aggiuntiva per gestire numeri pari e dispari 

int somma(int vett[], int n, int *e){
    int somma = 0;
    *e = 0; //viene modificato il valore della variabile a cui punta e

    for(int i = 0; i<ARR_LEN; i++){
        if(n == 0 && vett[i]%2 == 0){
            somma += vett[i];
            (*e)++;
        }
        else if(n == 1 && vett[i]%2 != 0){
            somma += vett[i];
            (*e)++;
        }
    }

    return somma;
}

float media(int somma, int elementi){
    if(elementi == 0){
        return 0;
    }
    else{
        return somma/elementi;
    }
}

int main() {
    struct sockaddr_in servizio, addr_remoto; 

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(servizio), vett[ARR_LEN], s, elementi;
    float m;

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

        if(read(soa, vett, sizeof(vett))<0)
        {
            printf("Errore nella read di vett");
            close(soa);
            continue;
        }

        //PARI
        s = somma(vett, 0, &elementi); //passiamo l'indirizzo di elementi

        if(send(soa, &s, sizeof(int), 0)<0){
            printf("Errore nella send di num");
            close(soa);
            continue;
        }

        m = media(s, elementi);
        
        if(send(soa, &m, sizeof(float), 0)<0){
            printf("Errore nella send di num");
            close(soa);
            continue;
        }

        //DISPARI
        s = somma(vett, 1, &elementi);

        if(send(soa, &s, sizeof(int), 0)<0){
            printf("Errore nella send di num");
            close(soa);
            continue;
        }

        m = media(s, elementi);
        
        if(send(soa, &m, sizeof(float), 0)<0){
            printf("Errore nella send di num");
            close(soa);
            continue;
        }

        close(soa);
    }

    close(socketfd);
    return 0;   
}