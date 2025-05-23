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
#define ARR_LEN 3

int main(int argc,char** argv)
{   
    struct sockaddr_in servizio, addr_remoto;  

    //inizializzazione dell'elemento di tipo sockaddr
    servizio.sin_family=AF_INET; 
    servizio.sin_addr.s_addr=htonl(INADDR_ANY); 
    servizio.sin_port=htons(SERVERPORT); 

    int socketfd, fromlen=sizeof(servizio), vett[ARR_LEN] = {2, 17, 1};
    float m;

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
    
    if(write(socketfd, vett, sizeof(vett))<0){
        printf("Errore nella write di vett");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    if(read(socketfd, vett, sizeof(vett))<0){
        printf("Errore nella recv di num");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<ARR_LEN; i++){
        printf("\n%d", vett[i]);
    }

    printf("\n");

    close(socketfd);
    return 0;
}
