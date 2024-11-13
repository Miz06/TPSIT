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

#define SERVERPORT 1313
#define ARR_LEN 4

int main(int argc,char** argv)
{   
    struct sockaddr_in servizio, addr_remoto;  

    //inizializzazione dell'elemento di tipo sockaddr
    servizio.sin_family=AF_INET; 
    servizio.sin_addr.s_addr=htonl(INADDR_ANY); 
    servizio.sin_port=htons(SERVERPORT); 

    int socketfd, fromlen=sizeof(servizio);
    double vett1[ARR_LEN] = {2, 4, 7, 8}, vett2[ARR_LEN] = {1, 2, 9, 1};

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

    if(write(socketfd, vett1, sizeof(vett1))<0){
        printf("Errore nella write di vett1");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    if(write(socketfd, vett2, sizeof(vett2))<0){
        printf("Errore nella write di vett2");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("\nVETT1: ");
    for(int i = 0; i<ARR_LEN; i++){
        printf("[%d] %f ", i, vett1[i] );
    }

    printf("\nVETT2: ");
    for(int i = 0; i<ARR_LEN; i++){
        printf("[%d] %f", i, vett2[i] );
    }

    printf("\nIn attesa di risposta dal server...\n");
    fflush(stdout);

    if(read(socketfd, vett1, sizeof(vett1))<0){
        printf("Errore nella read di vett1");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("\nSomma:\n");
    for(int i = 0; i<ARR_LEN; i++){
        printf("[%d] %f\n", i, vett1[i] );
    }

    if(read(socketfd, vett1, sizeof(vett1))<0){
        printf("Errore nella read di vett1");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("\n-------------------\n");

    printf("\nDifferenza:\n");
    for(int i = 0; i<ARR_LEN; i++){
        printf("[%d] %f\n", i, vett1[i] );
    }

    if(read(socketfd, vett1, sizeof(vett1))<0){
        printf("Errore nella read di vett1");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("\n-------------------\n");

    printf("\nProdotto:\n");
    for(int i = 0; i<ARR_LEN; i++){
        printf("[%d] %f\n", i, vett1[i]);
    }

    if(read(socketfd, vett1, sizeof(vett1))<0){
        printf("Errore nella read di vett1");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("\n-------------------\n");

    printf("\nQuoziente:\n");
    for(int i = 0; i<ARR_LEN; i++){
        printf("[%d] %f\n", i, vett1[i] );
    }

    printf("\n-------------------\n");
    close(socketfd);
    return 0;
}
