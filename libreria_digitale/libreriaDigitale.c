#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BOOKS 20
#define NUM_CATEGORIES 4

typedef struct{
    char title[30];
    char author[30];
    int year;
    float price;
}book;

typedef struct{
    char name[30];
    book books[NUM_BOOKS];
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

int main(){
    category categories[NUM_CATEGORIES];
    FILE *sourceFile = fopen("libreria_libri.csv", "r");

    if(sourceFile == NULL){
        printf("Error opening the file\n");
        return 1;
    }

    char line[1024];

    while(fgets(line, sizeof(line), sourceFile)){ //reading of the file's line
        char *token = strtok(line, ","); //al token viene assegnato il valore della stringa fino al raggiungimento della virgola
        while (token != NULL) {
            token = strtok(NULL, ","); 
        }
        printf("\n");
    }

    fclose(sourceFile);

    printCategory(categories, "arte");
    return 0;
}