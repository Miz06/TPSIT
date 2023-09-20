#include <stdio.h>

int main()
{
    //Alessandro Mizzon 
    /*Scrivi il codice sorgente di un programma che
    _ chiede all&#39;utente di fornire in ingresso due numeri interi, limite1 e limite2, compresi tra 30 e 50
    _ visualizza i valori di limite1 e limite2 solo qualora rispettino la consegna
    _ chiede all&#39;utente di fornire in ingresso cinque numeri interi che verranno salvati nella variabile n
    _ calcola la somma dei soli numeri, tra i cinque interi inseriti, che sono compresi tra limite1 e limite2
    _ visualizza il valore della variabile somma*/
    
    int limite1, limite2, somma = 0, numero; 

    do{
    printf("Inserire limite 1:"); 
    scanf("%d", &limite1); 
    }while(limite1<30 || limite1>50);

    do{
    printf("Inserire limite 2:"); 
    scanf("%d", &limite2); 
    }while(limite2<30 || limite2>50); 

    printf("%d", limite1);
    printf("\n"); 
    printf("%d", limite2); 
    printf("\n"); 

    for(int i = 0; i<5; i++)
    {
    printf("Inserire un numero:"); 
    scanf("%d", &numero); 

    if(numero>=30 && numero<=50)
    {
        somma += numero; 
    }
    }

    printf("Somma: "); 
    printf("%d", somma); 

}