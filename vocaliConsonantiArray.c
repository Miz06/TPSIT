include <stdio.h>
void main()
{
    char parola[5]; 
    int vocali = 0, consonanti = 0; 

    printf("Inserire una parola a piacere di 5 caratteri: \n");
    scanf("%s", parola); 

    for(int i = 0; i<5; i++)
    {
        if (parola[i] == 'a' || parola[i] == 'e' || parola[i] == 'i' || parola[i] == 'o' || parola[i] == 'u')
        {
            vocali++; 
        }
        else
        {
            consonanti++;
        }
    }

    printf("Le vocali contenute nella parola inserita sono: %d\n", vocali); 
    printf("I caratteri contenuti nella parola inserita sono: %d\n", consonanti); 

}
