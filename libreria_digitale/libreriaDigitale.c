#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BOOKS 20
#define NUM_CATEGORIES 4
#define BUFFER 2048

typedef struct{
    char title[30];
    char author[30];
    int year;
    float price;
}book;

typedef struct{
    char name[30];
    book books[NUM_BOOKS];
    int numLibriCategory;
}category;

int printCategory(category arr[], char categoryName[30]){
    for(int i = 0; i<NUM_CATEGORIES; i++){
        if(strcmp(arr[i].name, categoryName)){
            for(int j = 0; j<NUM_BOOKS; j++){
                printf("\nCATEGORY: %s\n", arr[i].name);

                printf("Title: %s\n", arr[i].books[j].title);
                printf("Author: %s\n", arr[i].books[j].author);
                printf("Year: %d\n", arr[i].books[j].year);
                printf("Title: %f\n-----------------------------\n", arr[i].books[j].price);
            }

            return 1;
        }
    }

    return 0;
}

void readCSV(category library[]){
    FILE *sourceFile = fopen("libreria_libri.csv", "r");
    int lenLibrary = sizeof(library)/sizeof(library[0]); //numero di categorie

    char riga[BUFFER]; //buffer per leggere una riga del file
    char searchCategory[30]; //categoria da ricercare nella libreria

    if(sourceFile == NULL){ //controllo apertura file
        printf("Error opening the file\n");
        return 1;
    }

    fgets(riga, BUFFER, sourceFile); //prima riga del file scartata

    while(fgets(riga, BUFFER, sourceFile) != NULL){ //lettura dall seconda riga in poi
        sscanf(riga, "%[^,],%[^,],%d,%f,%[^\r\n]", library[indexCategory]book.titolo, book.autore, &book.anno, &book.prezzo, categoria);

        int found = -1;

        for(int i = 0; i<sizeof(library)/sizeof(library[0]); i++){
            if(strrcasecmp(library[i].name, searchCategory) == 0){
                found = i;
                break;
            }
        }

        if(found == -1){
            found = library[]

        }
    }

    fclose(sourceFile);
}

int main(){
    category library[NUM_CATEGORIES]; //array di categorie: libreria



    printCategory(library, "arte");

    return 0;
}
