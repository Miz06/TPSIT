#include <stdio.h>
#include <stdlib.h>

    //TASTIERA E MONITOR SONO FILE
    // TASTIERA -> STANDARD INPUT 
    // MONITOR -> STANDART OUTPUT 

int main(){

    FILE *nomi; //variabile di tipo puntatore a file
    char vettNome[20]; 
    nomi = fopen("nomi.txt", "a"); //fopenlibreria ch mi da la possibilità di aprire o chiudere un file
    int exit = 0;                   //a: se il file è già stato modificato te lo lascia modificare da dove eri rimasto 
                                    //w: scrittura senza salvare i dati precedentemente inseriti    

    if(nomi ==NULL){
        printf("file non aperto: errore\n"); 
        exit = 1; 
    }else{
        printf("ok! file aperto\n");
    }

    for(int i = 0; i<4; i++)
    {
        printf("Inserisci il %d° nome: \n", i+1);
        scanf("%s", vettNome); 
        fputs(vettNome, nomi);
        fputc('\n', nomi); 
    }

    fclose(nomi); 


    return 0;
}