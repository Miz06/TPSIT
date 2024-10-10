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
    book books[NUM_BOOKS];
    int numBooksCategory;
}category;

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
    FILE *sourceFile = fopen("libreria_libri.csv", "r");
    char riga[BUFFER]; //buffer per leggere una riga del file
    int lenLibrary = 0;

    category library[NUM_CATEGORIES]; //array di categorie: libreria    
    char categorySup[100];
    book bookSup;

    if(sourceFile == NULL){ //controllo apertura file
        printf("Error opening the file\n");
        return 1;
    }

    fgets(riga, BUFFER, sourceFile); //prima riga del file scartata

    while(fgets(riga, BUFFER, sourceFile) != NULL){ //lettura dalla seconda riga in poi
        if (sscanf(riga, "%99[^,], %99[^,], %d, %f, %99[^\r\n]", bookSup.title, bookSup.author, &bookSup.year, &bookSup.price, categorySup) != 5) {
            printf("Error parsing the file\n");
            return 1;
        }

        int found = -1;

        for(int i = 0; i<lenLibrary; i++){
            if(!strcmp(library[i].name, categorySup)){
                found = i;
                break;
            }
        }

        if(found == -1){
            strcpy(library[lenLibrary].name, categorySup);
            library[lenLibrary].numBooksCategory = 0; // inizializza numBooksCategory a 0
            lenLibrary++;
        }

        if(library[found].numBooksCategory < NUM_BOOKS) {
            library[found].books[library[found].numBooksCategory] = bookSup;
            library[found].numBooksCategory++;
        }
    }

    fclose(sourceFile);
    printCategory(library, lenLibrary, "narrativa");
    
    return 0;
}