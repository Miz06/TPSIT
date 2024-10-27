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

int vowels(char str[DIM]){
    int v = 0;

    for(int i = 0; i<strlen(str); i++){
        if(!isdigit(str[i])){
            if(tolower(str[i]) == 'a' || tolower(str[i]) == 'e' || tolower(str[i]) == 'i' || tolower(str[i]) == 'o' || tolower(str[i]) == 'u'){
                v++;
            }
        }
    }
    
    return v;
}

int chars(char str[DIM]){
    int c = 0;

    for(int i = 0; i<strlen(str); i++){
        if(!isdigit(str[i])){
            if(tolower(str[i]) != 'a' && tolower(str[i]) != 'e' && tolower(str[i]) != 'i' && tolower(str[i]) != 'o' && tolower(str[i]) != 'u'){
                c++;
            }
        }
    }

    return c;
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;// record con i dati del server e del client

    servizio.sin_family=AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY);
    servizio.sin_port=htons(SERVERPORT);

    int socketfd, soa, fromlen=sizeof(servizio);
    char str[DIM];

    socketfd=socket(AF_INET,SOCK_STREAM,0);

    bind(socketfd,(struct sockaddr*)&servizio,sizeof(servizio));

    // poniamo il server in ascolto delle richieste dei client
    listen(socketfd,10);// può attendere fino a 10 client

    // ciclo infinito
    for (; ;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);

        soa=accept(socketfd,(struct sockaddr*)&addr_remoto,&fromlen);
        
        //legge dal client
        read(soa,str,sizeof(str));
        printf("\nStringa ricevuta: %s\n",str);
        close(soa);

        int v = vowels(str);
        send(soa, &v, sizeof(int), 0);

        int c = chars(str);
        send(soa, &c, sizeof(int), 0);

        close(soa);
    }

    close(socketfd);
    return 0;   
}