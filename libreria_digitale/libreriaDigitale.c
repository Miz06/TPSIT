#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BOOKS 40 //numero di libri di una categoria
#define NUM_CATEGORIES 4 //numero categorie della libreria
#define BUFFER 4096 //lunghezza del buffer utilizzato per leggere le singole righe

typedef struct{
    char title[100];
    char author[100];
    int year;
    float price;
}book;

typedef struct{
    char name[100];
    book books[NUM_BOOKS]; //array di libri contenuti in ogni categoria
    int numBooksCategory; //numero di libri contenuti in ogni categoria
}category;

int insertBooks(category library[], int lenLibrary){
    FILE *sourceFile = fopen("libreria_libri.csv", "r");
    char riga[BUFFER]; //buffer per leggere una riga del file
    char categorySup[100]; //stringa di supporto utilizzata per memorizzare la categoria del libro che verrà inserito
    book bookSup; //libro di supporto utilizzato per l'inserimento
    int found;

    if(sourceFile == NULL){ //controllo errore nell'apertura del file
        printf("Error opening the file\n");
        return 1;
    }

    fgets(riga, BUFFER, sourceFile); // scarto la prima riga del file in quanto contenente i campi dei libri

    while(fgets(riga, BUFFER, sourceFile) != NULL){ //lettura dalla seconda riga in poi
        if (sscanf(riga, "%99[^,], %99[^,], %d, %f, %99[^\r\n]", bookSup.title, bookSup.author, &bookSup.year, &bookSup.price, categorySup) != 5) {
            printf("Error parsing the file\n");
            return 1;
        }
        //una volta letta la riga del file i campi del libro di supporto assumono il valore degli attributi estratti
        //se sscaf non legge esattamente 5 valori dalla riga del file si ha un errore di parsing 

        found = -1; //variabile utilizzata per verificare la presenza o meno di una categoria all'interno della libreria

        for(int i = 0; i<lenLibrary; i++){
            if(!strcmp(library[i].name, categorySup)){
                found = i;
                library[found].books[library[found].numBooksCategory] = bookSup;
                library[found].numBooksCategory++;
                break;
            }
        }
        
        //nel ciclo viene controllato che la categoria del libro appena letto dal file che si vuole inserire nella libreria sia già presente nell’array o meno
        //n caso affermativo il libro viene inserito nell’array della categoria corrispondente.
        
        if(found == -1){
            strcpy(library[lenLibrary].name, categorySup);
            library[lenLibrary].numBooksCategory = 0; // inizializza numBooksCategory a 0
            library[lenLibrary].books[0] = bookSup;
            library[lenLibrary].numBooksCategory++;
            lenLibrary++;
        }

        //in caso contrario invece viene creata una nuova categoria e aggiunto il libro alla posizione 0 dell'array di libri della categoria appena creato
    }

    fclose(sourceFile);

    return lenLibrary;
}

void printCategory(category arr[], int lenArr, char categoryName[]){//metodo di stampa dela categoria 
    for(int i = 0; i<lenArr; i++){
        if(strcmp(arr[i].name, categoryName) == 0){
            for(int j = 0; j<arr[i].numBooksCategory; j++){
                printf("\nCATEGORY: %s\n", arr[i].name);

                printf("Title: %s\n", arr[i].books[j].title);
                printf("Author: %s\n", arr[i].books[j].author);
                printf("Year: %d\n", arr[i].books[j].year);
                printf("Price: %f\n-----------------------------\n", arr[i].books[j].price);
            }

            break;
        }
    }
}

int main(){
    category library[NUM_CATEGORIES]; //array di categorie: libreria    
    int lenLibrary = 0; //numero di categorie inserite
    int choice; 

    lenLibrary = insertBooks(library, lenLibrary);

    do{//menù di inserimento per gestire la visualizzazione dei libri di una categoria
        printf("\n[CATEGORIE]\n[1] narrativa\n[2] saggistica\n[3] arte\n[4] scienza\n");
        printf("\nCategoria di libri da cercare:");
        scanf("%d", &choice);

        if(choice<1||choice>4){
            printf("Inserire un valore valido!\n");
        }
    }while(choice<1||choice>4);

    switch(choice){
        case(1):
            printCategory(library, lenLibrary, "narrativa");
            break;
        case(2):
            printCategory(library, lenLibrary, "saggistica");
            break;
        case(3):
            printCategory(library, lenLibrary, "arte");
            break;
        case(4):
            printCategory(library, lenLibrary, "scienza");
            break;
    }

    return 0;
}
