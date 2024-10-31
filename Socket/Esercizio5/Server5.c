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
#include <arpa/inet.h>

#define DIM 50
#define SERVERPORT 1313

void ordinaStringa(char str[DIM]){
    char sup;
    
    for(int i = 0; i<strlen(str); i++){
        for(int j = i+1; j<strlen(str); j++){
            if((int)tolower(str[i])>(int)tolower(str[j])){
                sup = str[i];
                str[i] = str[j];
                str[j] = sup;
            }
        }

    }
}

int main() {
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);

    const char* ip_server = "192.168.2.205"; // Indirizzo IP del client

    if (inet_pton(AF_INET, ip_server, &servizio.sin_addr) <= 0) {
        perror("Errore nella conversione dell'indirizzo IP");
        exit(EXIT_FAILURE);
    }

    int socketfd, soa, fromlen = sizeof(servizio);
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
        
        if(read(soa, str, sizeof(str))<0)
        {
            printf("Errore nella read della stringa");
            close(soa);
            continue;
        }

        printf("\nStringa ricevuta: %s\n", str);

        ordinaStringa(str);

        if(write(soa, &str, sizeof(str))<0){
            printf("Errore nella write di str");
            close(soa);
            exit(EXIT_FAILURE);
        }

        close(soa);
    }

    close(socketfd);
    return 0;   
}