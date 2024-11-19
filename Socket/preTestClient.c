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
#include <ctype.h> //per poter utilizzare funzione come isaigit(), isalpha(), islower(), isupper(), tolower(), toupper()

#define SERVER_PORT 1313

int main(){
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVER_PORT);

    int socketfd, num = 4;
    char vett[20] = {30, 20, 4, 1};

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    send(socketfd, &num, sizeof(int), 0);
    write(socketfd, vett, sizeof(vett));

    close(socketfd);
    return 0;
}