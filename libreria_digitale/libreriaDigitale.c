#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BOOKS 40
#define NUM_CATEGORIES 4
#define BUFFER 4096

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
    char categorySup[100]; //categoria di supporto utilizzata per memorizzare la categoria del libro che verrà inserito
    book bookSup; //libro di supporto utilizzato per l'inserimento
    int found;

    if(sourceFile == NULL){
        printf("Error opening the file\n");
        return 1;
    }

    fgets(riga, BUFFER, sourceFile); 


    while(fgets(riga, BUFFER, sourceFile) != NULL){ //lettura dalla seconda riga in poi
        if (sscanf(riga, "%99[^,], %99[^,], %d, %f, %99[^\r\n]", bookSup.title, bookSup.author, &bookSup.year, &bookSup.price, categorySup) != 5) {
            printf("Error parsing the file\n");
            return 1;
        }

        found = -1;

        for(int i = 0; i<lenLibrary; i++){
            if(!strcmp(library[i].name, categorySup)){
                found = i;
                library[found].books[library[found].numBooksCategory] = bookSup;
                library[found].numBooksCategory++;
                break;
            }
        }

        if(found == -1){
            strcpy(library[lenLibrary].name, categorySup);
            library[lenLibrary].numBooksCategory = 0; // inizializza numBooksCategory a 0
            library[lenLibrary].books[0] = bookSup;
            library[lenLibrary].numBooksCategory++;
            lenLibrary++;
        }
    }

    fclose(sourceFile);

    return lenLibrary;
}

void printCategory(category arr[], int lenArr, char categoryName[]){
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

    do{
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
