//Nel codice del 20 abbiamo: utilizzato execl (che prende come argomenti nome file e stringhe), passato una struct tramite la fifo
//Nel codice seguente abbiamo: utilizzato execv (che prende come argomenti nome file e array di stringhe), scritto e letto su file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//definizione costanti
#define BLOCK_DIM 1024 
#define PROGRAM "writer"

//funzione di spawn 
int spawn(char program[], char *argument[])
{
  int pid;
  pid = fork();//Creazione figlio

  if (pid < 0)
    return -1;
  if (pid > 0)
    return 0;
  execv(program, argument);//mando in eseguzione program con argomenti l'array argument
  abort();//Se l'esecuzione non va a buon fine il figlio viene terminato 
}

int main(int argc, char *argv[])
{
  FILE *file;
  int fifo;
  unsigned char buffer[BLOCK_DIM];
  int n;
  char *arg[3];

  if (argc != 3)//Gestione errore passaggio parametri
  {
    printf("Uso: %s file-origine file-destinazione\r\n", argv[0]);
    return 0;
  }

  //creo la riga di comando che passerò al figlio
  //questa serve a mandare in esecuzione il processo consumatore, writer
  arg[0] = (char *)malloc(strlen(PROGRAM) + 1);
  strcpy(arg[0], PROGRAM);
  arg[1] = (char *)malloc(strlen(argv[2]) + 1);
  strcpy(arg[1], argv[2]);
  arg[2] = NULL;

  if (spawn(PROGRAM, arg) < 0)//Creazione del processo tramite i parametri PROGRAM (nome del file) e arg (array di stringhe: argomenti)
  {//Gestione errore creazione processo
    printf("Errore creazione processo\r\n");
    free(arg[0]);//Deallocazione manuale della memoria 
    free(arg[1]);//Deallocazione manuale della memoria
    return 0;
  }

  fifo = open("my_fifo", O_WRONLY);//Apro la fifo in scrittura
  if (fifo < 0)//Gestione errore apertura fifo
  {
    printf("Errore apertura FIFO\r\n");
    free(arg[0]);//Deallocazione manuale della memoria
    free(arg[1]);//Deallocazione manuale della memoria
    return 0;
  }

  file = fopen(argv[1], "rb");//Apertura del file (il cui nome è passato come argomento) in lettura (file binario)
  if (file == NULL)//Gestione errore apertura file
  {
    printf("Errore apertura file \"%s\"\r\n", argv[1]);
    close(fifo);//Chiudo fifo
    free(arg[0]);//Deallocazione manuale della memoria
    free(arg[1]);//Deallocazione manuale della memoria
    return 0;
  }
  while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0)//finchè n restituisce un valore maggiore di 0 il ciclo si ripete
    write(fifo, buffer, n);//scrivo nella fifo ciò che è contenuto nel buffer (nonchè ciò che ho letto dalla read)
  fclose(file);//Chiudo file
  close(fifo);//Chiudo fifo
  free(arg[0]);//Deallocazione manuale della memoria
  free(arg[1]);//Deallocazione manuale della memoria
  return 1;
}
