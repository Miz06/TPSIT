#include <stdio.h>
#include <string.h>

#define LEN 4

typedef struct{
    char modelloAuto[30];
    char marca[30];
    int cilindrata;
    int prezzo;
    int annoImmatricolazione;
}Auto;

void stampa(Auto arr[]){
    for(int i = 0; i<LEN; i++){
        printf("Modello: %s\nMarca: %s\nCilindrata: %d\nPrezo: %d\nAnno immatricolazione: %d\n\n", arr[i].modelloAuto, arr[i].marca, arr[i].cilindrata, arr[i].prezzo, arr[i].annoImmatricolazione);
    }
}

Auto moreExprensive(Auto arr[]){
    Auto car = arr[0];
    
    for(int i = 1; i<LEN; i++){
        if(car.prezzo<arr[i].prezzo)
        {
            car = arr[i];
        }
    }
    
    return car;
}

Auto lessExprensive(Auto arr[]){
    Auto car = arr[0];
    
    for(int i = 1; i<LEN; i++){
        if(car.prezzo>arr[i].prezzo)
        {
            car = arr[i];
        }
    }
    
    return car;
}

void ordinaArray(Auto arr[]){
    Auto sup;
    
    for(int i = 0; i<LEN; i++){
        for(int j = 0; j<LEN; j++){
            if(arr[i].annoImmatricolazione>arr[j].annoImmatricolazione){
                sup = arr[i];
                arr[i] = arr[j];
                arr[j] = sup;
            }
        }
    }
}

void stampaDaPrezzo(Auto arr[], int prezzo){
    for(int i = 0; i<LEN; i++){
        if(arr[i].prezzo <= prezzo){
            printf("Modello: %s\nMarca: %s\nCilindrata: %d\nPrezo: %d\nAnno immatricolazione: %d\n\n", arr[i].modelloAuto, arr[i].marca, arr[i].cilindrata, arr[i].prezzo, arr[i].annoImmatricolazione);
        }
    }
}

int main(int argc, char *argv[])
{
    Auto arr[LEN];
    
    strcpy(arr[0].modelloAuto, "modello1");
    strcpy(arr[0].marca, "marca1");    
    arr[0].cilindrata = 1600;
    arr[0].prezzo = 20000;
    arr[0].annoImmatricolazione = 2010;
    
    strcpy(arr[1].modelloAuto, "modello2");
    strcpy(arr[1].marca, "marca2");    
    arr[1].cilindrata = 1800;
    arr[1].prezzo = 25000;
    arr[1].annoImmatricolazione = 2015;
    
    strcpy(arr[2].modelloAuto, "modello3");
    strcpy(arr[2].marca, "marc3");    
    arr[2].cilindrata = 2000;
    arr[2].prezzo = 22000;
    arr[2].annoImmatricolazione = 2016;
    
    strcpy(arr[3].modelloAuto, "modello4");
    strcpy(arr[3].marca, "marca4");    
    arr[3].cilindrata = 1700;
    arr[3].prezzo = 18000;
    arr[3].annoImmatricolazione = 2008;
    
    Auto moreExprensiveAuto = moreExprensive(arr);
    Auto lessExprensiveAuto = lessExprensive(arr);
    
    printf("\n1)\nAUTO PIU' COSTOSA\nPrezzo: %d\nModello: %s\n", moreExprensiveAuto.prezzo, moreExprensiveAuto.modelloAuto);
    printf("\nAUTO MENO COSTOSA\nPrezzo: %d\nModello: %s\n", lessExprensiveAuto.prezzo, lessExprensiveAuto.modelloAuto);
    
    printf("\n2)\n");
    ordinaArray(arr);
    stampa(arr);
    
    printf("\n3)\n");
    int prezzo;
    printf("Prezzo di partenza: ");
    scanf("%d", &prezzo);
    printf("\n");
    
    stampaDaPrezzo(arr, prezzo);
    
    return 0;
}