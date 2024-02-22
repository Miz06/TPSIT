#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Creare una biblioteca (3 libri) dove ogni libro ha un titolo, un autore e un prezzo;
 queste tre caratteristiche sono introdotte dall'utente.
Realizzare:
-1 un metodo per inserire i valori scelti dall'utente;

-1 un metodo per stampare il contenuto della bilblioteca(titolo, autore, prezzo);

-2 un metodo per applicare uno sconto al prezzo dei libri (il metodo riceve lo sconto in ingresso,
 per esempio 10% e sconta tutti i libri del 10%. Questo sconto è inserito dall'utente).
Nel main chiamare i metodi1,2.3 e ancora 1 per vedere se lo sconto è stato applicato correttamente.
NELL'IMPLEMENTAZIONE E' OBBLIGATORIO L'UTILIZZO DEI PUNTATORI*/

    typedef struct
    {
        char titolo[50];
        char autore[50]; 
        float prezzo;
    }libro;
        
    void Inserimento(libro *array[], int i)
    {
            printf("Inserire il titolo del %d° libro: \n", i+1); 
            scanf("%s", array[i]->titolo); 
            printf("Inserire l'autore del %d° libro: \n", i+1);
            scanf("%s", array[i]->autore); 
            printf("Inserire il prezzo %d° libro: \n", i+1);
            scanf("%f", &array[i]->prezzo);
    }

    void Visualizzazione(libro *array[], int lung)
    {
        for(int i = 0; i<lung; i++)
        {
            printf("--------------------\n"); 
            printf("Libro %d\n", i+1);
            printf("Titolo: %s\n", array[i]->titolo);
            printf("Autore: %s\n", array[i]->autore);
            printf("Prezzo: %.2f\n", array[i]->prezzo);
            printf("--------------------\n"); 
        }
    }

    void Sconto(libro *array[], int lunghezza)
    {
        float sconto;
        printf("Inserire lo sconto da applicare ai libri:\n");
        scanf("%f", &sconto); 

        for(int i = 0; i<lunghezza; i++)
        {
            array[i]->prezzo = array[i]->prezzo-((array[i]->prezzo)/100)*sconto; 
        }
    }

    int main()
    { //Alessandro Mizzon 4E
        const int lung = 3;
        float sconto;
        libro *biblioteca[lung]; 
        
        for(int i = 0; i<lung; i++)
        {
            biblioteca[i] = ((libro *)malloc(sizeof(libro)));
            Inserimento(biblioteca, i);
        }

        Visualizzazione(biblioteca, lung); 

        Sconto(biblioteca, lung);

        Visualizzazione(biblioteca, lung); 

        for(int i = 0; i<lung; i++)
        {
            free(biblioteca[i]);
        }
    return 0; 
    }