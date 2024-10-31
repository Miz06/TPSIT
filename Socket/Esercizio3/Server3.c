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

int palindroma(char str[]){
    char sup[strlen(str)-1];

    for(int i = 0; i<strlen(str); i++){
        sup[strlen(str)-i-1] = str[i];
    }

    sup[strlen(str)] = '\0';

    if(strcmp(sup, str)){
        return 1;
    }
    else{
        return 0;
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto; // record con i dati del server e del client

    servizio.sin_family=AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY);
    servizio.sin_port=htons(SERVERPORT);

    int socketfd, soa, fromlen=sizeof(servizio), p;
    char str[DIM];

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
            printf("Errore nella read di str");
            close(soa);
            continue;
        }

        printf("\nStringa ricevuta: %s\n",str);

        p = palindroma(str);

        if(send(soa, &p, sizeof(int), 0)<0){
            printf("Errore nella send di p");
            close(soa);
            continue;
        }

        close(soa);
    }

    close(socketfd);
    return 0;   
}