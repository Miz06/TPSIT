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
    int numBooks;
}category;

int printCategory(category arr[], char categoryName[30]){
    for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); i++){
        if(strcmp(arr[i].name, categoryName) == 0){
            for(int j = 0; j<arr[i].numBooks; j++){
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

int main(){
    FILE *sourceFile = fopen("libreria_libri.csv", "r");
    char riga[BUFFER]; //buffer per leggere una riga del file

    category library[NUM_CATEGORIES]; //array di categorie: libreria
    int lenLibrary = sizeof(library)/sizeof(library[0]); //numero di categorie contenute attualmente (bytes arr/bytes elemento = elementi dell'array)
    
    char categorySup[20];
    book bookSup;

    if(sourceFile == NULL){ //controllo apertura file
        printf("Error opening the file\n");
        return 1;
    }

    fgets(riga, BUFFER, sourceFile); //prima riga del file scartata

    while(fgets(riga, BUFFER, sourceFile) != NULL){ //lettura dalla seconda riga in poi
        sscanf(riga, "%[^,],%[^,],%d,%f,%[^\r\n]", bookSup.titolo, bookSup.autore, &bookSup.anno, &bookSup.prezzo, categorySup);//butta dentro bookSup i rispettivi campi della riga
        
        int found = -1;

        for(int i = 0; i<lenLibrary; i++){
            if(strcmp(library[i].name, categorySup) == 0){
                found = i;
                library[i].books[library[i].numBooks] = bookSup;
                library[i].numBooks++;
                break;
            }
        }

        if(found == -1){
            strcpy(library[lenLibrary].name, categorySup);
            library[lenLibrary].books[0] = bookSup;
            library[lenLibrary].numBooks++;
        }
    }

    fclose(sourceFile);
    printCategory(library, "narrativa");
    return 0;
}
