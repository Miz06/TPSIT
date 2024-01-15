/*Creare un programma in C che genera una sequenza di 10.000
numeri casuali e li memorizza in un array; i numeri generati devono appartenere
all’intervallo 1-500.
Nel programma il processo padre genera due figli e la
suddivisione dei compiti deve essere come segue:
-         Il padre genera i 10.000 numeri casuali.
-         Il padre salva tutti i numeri casuali in un file con il formato indice_array : valore
-         Il padre ricerca all’interno dei primi 2000 numeri dell’array un numero X inserito dall’utente a linea di comando e stampa a video la coppia indice_array : valore per tutte le coppie trovate; la stampa di ogni coppia deve essere preceduta dal pid del processo.
-         I due figli svolgono lo stesso compito del punto precedente dividendosi il lavoro a metà (4000 ricerche ciascuno).*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DIM 10000

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore degli argomenti");
    }

    int arr[DIM];
    FILE *file;
    int p;

    for (int i = 0; i < DIM; i++)
    {
        arr[i] = rand() % 500 + 1;
    }

    file = fopen("text.txt", "w");

    if (file == NULL)
    {
        printf("Errore nell'apertura del file");
    }
    else
    {
        for (int i = 0; i < DIM; i++)
        {
            if (i != 9999)
                fprintf(file, "[%d] %d\n", i, arr[i]);
            else
            {
                fprintf(file, "[%d] %d", i, arr[i]);
            }
        }

        fclose(file);
    }

    int numero = atoi(argv[1]);

    p = fork();

    if (p > 0)
    {
        for (int i = 0; i < 2000; i++)
        {
            if (arr[i] == numero)
            {
                printf("PID: %d - PID figlio: %d - Numero trovato in posizione %d\n", getpid(), p, i);
            }
        }

        p = fork();

        if (p == 0)
        {
            for (int i = 2000; i < 6000; i++)
            {
                if (arr[i] == numero)
                {
                    printf("PID: %d - PID padre: %d - Numero trovato in posizione %d\n", getpid(), getppid(), i);
                }
            }
        }
    }

    if (p == 0)
    {
        for (int i = 6000; i < 10000; i++)
        {
            if (arr[i] == numero)
            {
                printf("PID: %d - PID padre: %d - Numero trovato in posizione %d\n", getpid(), getppid(), i);
            }
        }
    }

    return 0;
}
