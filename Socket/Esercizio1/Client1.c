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

int main(int argc,char** argv)
{   
    struct sockaddr_in servizio, addr_remoto; //INDIRIZZO IP - PORTA - DOMINIO 

    //inizializzazione dell'elemento di tipo sockaddr
    servizio.sin_family=AF_INET; 
    servizio.sin_addr.s_addr=htonl(INADDR_ANY); 
    servizio.sin_port=htons(SERVERPORT); 

    char str[DIM];
    int socketfd, fromlen=sizeof(servizio);

    socketfd=socket(AF_INET,SOCK_STREAM,0); 

    connect(socketfd,(struct sockaddr*)&servizio,fromlen);
    printf("Inserisci la stringa\n");
    scanf("%s",str);
    write(socketfd,str,sizeof(str));

    printf("\n\nServer in ascolto...");
    fflush(stdout);

    //legge dal server
    read(socketfd, str,sizeof(str));
    printf("\nStringa in maiuscolo: %s\n",str);
    close(socketfd);

    close(socketfd);
    return 0;
}
