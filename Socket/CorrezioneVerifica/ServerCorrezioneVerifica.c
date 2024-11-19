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

void popolaVettore(int vett1[], int vett2[], int num, int pos){    
    for(int i = 0; i<pos; i++){
        vett2[i] = vett1[i];
    }

    vett2[pos] = num;
    
    for(int i = pos+1; i<ARR2_LEN; i++){
        vett2[i] = vett1[i-1];
    }
}

int main(){
    struct sockaddr_in servizio, addr_remoto; //Creazione elementi di tipo sockaddr

    //inizializzazione dell'elemento servizio
    servizio.sin_family = AF_INET; //AF_INET consente di utilizzare la famiglia degli indirizzi IPv4
    servizio.sin_addr.s_addr = htonl(INADDR_ANY); //con INADDR_ANY viene utilizzato un qualsiasi indirizzo disponibile
    servizio.sin_port = htons(SERVER_PORT); //viene espressa la porta del server

    int socketfd, soa, len=sizeof(servizio);
    int vett1[ARR1_LEN], vett2[ARR2_LEN], num, pos;

    //Controllo sulla ceazione della socket TCP/IP
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf("Errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }

    //Controllo sull'impostazione del transport endpoint del server
    if(bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio))<0){
        printf("Errore nella impostazione del transport endpoint");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    //Controllo sull'impostazione del server in grado di gestire fino a 10 utenti
    if(listen(socketfd, 10)<0){
        printf("Errore nella listen");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    for(; ;)
    {//Il server rimane in ascolto fino a quando non viene interrotto
        printf("\nServer in ascolto...\n");
        fflush(stdout);

        //Controllo sul server che accetta la connessione con il client
        if((soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &len))<0){
            printf("Errore nella soa");
            exit(EXIT_FAILURE);
            close(soa);
        }

        if(read(soa, vett1, sizeof(vett1))<0){
            printf("Errore nella ricezione del vettore dal client");
            exit(EXIT_FAILURE);
            continue;
        }

        if(recv(soa, &num, sizeof(int), 0)<0){
            printf("Errore nella ricezione del numero (da inserire nel vettore) dal client");
            exit(EXIT_FAILURE);
            continue;
        }

        if(recv(soa, &pos, sizeof(int), 0)<0){
            printf("Errore nella ricezione del numero (posizione del numero) dal client");
            exit(EXIT_FAILURE);
            continue;
        }

        popolaVettore(vett1, vett2, num, pos);

        if(write(soa, vett2, sizeof(vett2))<0){
            printf("Errore nell'invio del nuovo vettore dal client");
            exit(EXIT_FAILURE);
            continue;
        }

        close(soa);
    }

    close(socketfd);
    return 0;
}