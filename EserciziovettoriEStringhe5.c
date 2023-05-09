#include <stdio.h>
int main()
{
    char parola[100];
    char parola2[100]; 
    int pari[100]; 
    int dispari[100]; 
    int p=0, d=0, vocali1=0, vocali2=0, consonanti1=0, consonanti2=0; 
    
    printf("Inserire una parola:");
    scanf("%s", parola);
    	
    for (int i = 0; i<strlen(parola); i++)
    {
        if (i % 2 == 0)
        {
            pari[p]=parola[i]; 
            p++; 
        }
        else
        {
            dispari[d]=parola[i]; 
            d++; 
        }
    }
    
    printf("Lettere in posizione pari: "); 
    for(int i = 0; i<p; i++)
    {
        printf("%s", &pari[i]);         
    }
    
    printf("\n"); 
    printf("Lettere in posizione pari: "); 
    for(int i = 0; i<d; i++)
    {
        printf("%s", &dispari[i]);         
    }
    
    printf("\n"); 
    printf("Inserire un'altra parola:"); 
    scanf("%s", parola2); 
    
    if (strlen(parola2)>strlen(parola))
    {
        printf("La secona parola inserita è la più lunga");
    }
    else if (strlen(parola2)<strlen(parola))
    {
        printf("La prima parola inserita è la più lunga");
    }
    else if (strlen(parola2)==strlen(parola))
    {
        printf("Le due parole inserite hanno la stessa lunghezza");
    }
    
    for (int i = 0; i<strlen(parola); i++)
    {
        if(parola[i]=='a' || parola[i]=='e' || parola[i]=='i' || parola[i]=='o' || parola[i]=='u')
        {
            vocali1++; 
        }   
        else
        {
            consonanti1++; 
        }
    }
    
    for (int i = 0; i<strlen(parola2); i++)
    {
        if(parola2[i]=='a' || parola2[i]=='e' || parola2[i]=='i' || parola2[i]=='o' || parola2[i]=='u')
        {
            vocali2++; 
        }   
        else
        {
            consonanti2++; 
        }
    }
    
    printf("\n"); 
    if (vocali1>vocali2)
    {
        printf("La prima parola contiene più vocali");
    }
    else if (vocali1<vocali2)
    {
        printf("La seconda parola contiene più vocali");
    }
    else if (vocali1==vocali2)
    {
        printf("Le due parole hanno lo stesso numero di vocali");
    }
    
    printf("\n"); 
    if (consonanti1>consonanti2)
    {
        printf("La prima parola contiene più consonanti");
    }
    else if (consonanti1<consonanti2)
    {
        printf("La seconda parola contiene più consonanti");
    }
    else if (consonanti1==consonanti2)
    {
        printf("Le due parole hanno lo stesso numero di consonanti");
    }
    
    
    
    
    
    
    
    
    
    
    

}
