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
#include <ctype.h> //per poter utilizzare funzione come isaigit(), isalpha(), islower(), isupper(), tolower(), toupper()

#define SERVER_PORT 1313

int main(){
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVER_PORT);

    int socketfd, soa, fromlen=sizeof(servizio), num;
    char vett[20];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr*)&servizio, fromlen);

    listen(socketfd, 10);

    for(; ;){
        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);

        if(recv(soa, &num, sizeof(int), 0)<0)
        {
            perror("Error: ");
            exit(EXIT_FAILURE);
            continue;
        }

        read(soa, vett, sizeof(vett));

        printf("Numero: %d", num);
    
        for(int i = 0; i<4; i++)
        {
            printf("\n%c\n", vett[i]);
        }

        close(soa);
    }

    close(socketfd);
    return 0;
}