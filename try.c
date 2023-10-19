#include <stdio.h>
#include <stdlib.h>

    //TASTIERA E MONITOR SONO FILE
    // TASTIERA -> STANDARD INPUT 
    // MONITOR -> STANDART OUTPUT 

int main(){

    FILE *nomi; //variabile di tipo puntatore a file
    char c; 
    nomi = fopen("nomi.txt", "r"); //fopenlibreria ch mi da la possibilità di aprire o chiudere un file
    int exit = 0;                   //a: se il file è già stato modificato te lo lascia modificare da dove eri rimasto 
                                    //w: scrittura senza salvare i dati precedentemente inseriti    

    if(nomi ==NULL){
        printf("file non aperto: errore\n"); 
        exit = 1; 
    }
    
    do{
        c = fgetc(nomi);
        putchar(c);
    }while(c!=(EOF));

    fclose(nomi); 


    return 0;
}