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

void printCategory(category arr[], int lenArr, char categoryName[30]){
    for(int i = 0; i<lenArr; i++){
        if(strcmp(arr[i].name, categoryName) == 0){
            for(int j = 0; j<arr[i].numBooks; j++){
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
    char categorySup[20];
    book bookSup;

    if(sourceFile == NULL){ //controllo apertura file
        printf("Error opening the file\n");
        return 1;
    }

    fgets(riga, BUFFER, sourceFile); //prima riga del file scartata

    fgets(riga, BUFFER, sourceFile); //seconda riga del file scartata
    sscanf(riga, "%[^,],%[^,],%d,%f,%[^\r\n]", bookSup.title, bookSup.author, &bookSup.year, &bookSup.price, categorySup);//butta dentro bookSup i rispettivi campi della riga

    library[0].books[0] = bookSup;
    library[0].numBooks=0;
    library[0].numBooks++;
    strcpy(library[0].name, categorySup);
    lenLibrary++;

    while(fgets(riga, BUFFER, sourceFile) != NULL){ //lettura dalla seconda riga in poi
        sscanf(riga, "%[^,],%[^,],%d,%f,%[^\r\n]", bookSup.title, bookSup.author, &bookSup.year, &bookSup.price, categorySup);//butta dentro bookSup i rispettivi campi della riga

        int found = -1;

        for(int i = 0; i<lenLibrary; i++){
            if(!strcmp(library[i].name, categorySup)){
                printf("Ciao");
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
            lenLibrary++;
        }
    }

    fclose(sourceFile);
    
    printCategory(library, lenLibrary, "narrativa");
    
    return 0;
}
