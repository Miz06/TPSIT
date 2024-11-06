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

void max_min(int vett[], int *max, int *min){
    *max = vett[0];
    *min = vett[0];

    for(int i = 1; i<ARR_LEN; i++){
        if(vett[i]>*max){
            *max = vett[i];
        }

        if(vett[i]<*min){
            *min = vett[i];
        }
    }
}

int main() {
    struct sockaddr_in servizio, addr_remoto; 

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(servizio), vett[ARR_LEN], value;
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

        int max, min;
        max_min(vett, &max, &min);

        if(send(soa, &max, sizeof(int), 0)<0){
            printf("Errore nella send di max");
            close(soa);
            continue;
        }

        if(send(soa, &min, sizeof(int), 0)<0){
            printf("Errore nella send di min");
            close(soa);
            continue;
        }

        close(soa);
    }

    close(socketfd);
    return 0;   
}