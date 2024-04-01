//Nel codice del 20 abbiamo: utilizzato execl (che prende come argomenti nome file e stringhe), passato una struct tramite la fifo
//Nel codice seguente abbiamo: utilizzato execv (che prende come argomenti nome file e array di stringhe), scritto e letto su file

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//definizione costanti
#define BLOCK_DIM 1024

int main(int argc, char *argv[])
{
     FILE *file;
     unsigned char buffer[BLOCK_DIM];
     int n;
     int fifo;

     if (argc != 2)//Gestione errore passaggio parametri
     {
          printf("Uso: %s file\r\n", argv[0]);
          return 0;
     }

     fifo = open("my_fifo", O_RDONLY);//Apertura della fifo in lettura
     if (fifo < 0)//Controllo errore apertura fifo
     {
          printf("Errore apertura FIFO\r\n");
          return 0;
     }
     file = fopen(argv[1], "wb");//Apertura del file (il cui nome è passato come argomento) in scrittura (file binario)
     if (file == NULL)//Controllo errore apertura file
     {
          printf("Errore apertura file \"%s\"\r\n", argv[1]);
          close(fifo);
          return 0;
     }
     while ((n = read(fifo, buffer, sizeof(buffer))) > 0) //finchè n restituisce un valore maggiore di 0 il ciclo si ripete
          fwrite(buffer, 1, n, file);//scrivo nel file ciò che è contenuto nel buffer (nonchè ciò che ho letto dalla read)
     close(fifo);//Chiudo fifo
     fclose(file);//Chiudo file
     return 1;
}
