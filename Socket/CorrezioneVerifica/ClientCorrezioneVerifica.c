//ALESSANDRO MIZZON - 5E - FILA 3

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define SERVER_PORT 1313
#define ARR1_LEN 4
#define ARR2_LEN 5

int main(int agrc, char *argv[]){
    struct sockaddr_in servizio; //creazione di un elemento di tipo sockaddr

    //inizializzazione dell'elemento servizio
    servizio.sin_family = AF_INET; //AF_INET consente di utilizzare la famiglia degli indirizzi IPv4
    servizio.sin_addr.s_addr = htonl(INADDR_ANY); //con INADDR_ANY viene utilizzato un qualsiasi indirizzo disponibile
    servizio.sin_port = htons(SERVER_PORT); //viene espressa la porta del server

    int socketfd; //identificatore della socket
    int vett1[ARR1_LEN], vett2[ARR2_LEN], num, pos;

    //Controllo sulla ceazione della socket TCP/IP
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf("Errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }

    //Controllo sulla connesssione del client al server
    if(connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio))<0){
        printf("Errore nella connesione al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    //inserisco in vett1 i valori inseriti da linea di comando ovviamente non consideranto il nome del file in posizione 0
    for(int i = 0; i<ARR1_LEN; i++){
        vett1[i] = atoi(argv[i+1]);
    }

    //di conseguenza assegno a num e pos il loro valore in base ai numeri inseriti da liena di comando
    num = atoi(argv[ARR1_LEN+1]);
    pos = atoi(argv[ARR1_LEN+2]);

    if(write(socketfd, vett1, sizeof(vett1))<0){
        printf("Errore nell'invio del vettore al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    if(send(socketfd, &num, sizeof(int), 0)<0){
        printf("Errore nell'invio del numero (da aggiungere al vettore) al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    
    if(send(socketfd, &pos, sizeof(int), 0)<0){
        printf("Errore nell'invio del numero (che esprime la posizione del numero nel vettore) al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    if(read(socketfd, vett2, sizeof(vett2))<0){
        printf("Errore nella ricezione del nuovo vettore dal server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<ARR2_LEN; i++){
        printf("\n%i) %d\n", i, vett2[i]);
    }

    close(socketfd);
    return 0;
}