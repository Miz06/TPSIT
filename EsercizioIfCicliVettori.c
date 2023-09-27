#include <stdio.h>

int main()
{
    int limite1, limite2, somma = 0;
    int n[5]; 

    do
    {
    printf("Inserire limite1:"); 
    scanf("%d", &limite1); 

    printf("Inserire limite2:"); 
    scanf("%d", &limite2); 
    }while(limite1<30 || limite2<30 || limite1>50 || limite2>50);

    printf("     \n"); 
    printf("Limite1: %d\n", limite1); 
    printf("Limite2: %d\n", limite2); 
    printf("     \n"); 
    
    for(int i =0; i<5; i++)
    {
        printf("Inserire il %d° numero: ", i+1); 
        scanf("%d", &n[i]); 
    }
    
    printf("     \n"); 
    printf("Array: \n"); 
    for(int i =0; i<5; i++)
    {
        printf("%d\n", n[i]); 
    }

    printf("     \n"); 

    for(int i =0; i<5; i++)
    {
        if(n[i]>=limite1 && n[i]<=limite2)
        {
            printf("Indice: %d\n", i); 
            printf("Posizione: %d\n", i+1); 
            printf("Elemento: %d\n", n[i]); 
            printf("--------------------\n"); 
            somma += n[i]; 
        }
    }

    printf("Somma: %d\n", somma);

}