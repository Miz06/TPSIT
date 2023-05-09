#include <stdio.h>

int main()
{//Alessandro Mizzon 
    char stringa1[100]; 
    char stringa2[100]; 
    int lunghezza, c=0, b=0;
    char comuni[100]; 
    
    printf("Inserire la prima stringa:");
    scanf("%s", stringa1); 
    printf("Inserire la seconda stringa:");
    scanf("%s", stringa2); 

    if(strlen(stringa1)>strlen(stringa2))
    {
        lunghezza = strlen(stringa1); 
    }
    else if(strlen(stringa1)<strlen(stringa2))
    {
        
        lunghezza = strlen(stringa2);
    }
    else if(strlen(stringa1)==strlen(stringa2))
    {
        
        lunghezza = strlen(stringa1); 
    }
    
    
    for(int i = 0; i<lunghezza; i++)
    {
        for(int j=0; j<lunghezza; j++)
        {
            if(stringa1[i]==stringa2[j])
            {
                comuni[c]=stringa1[i]; 
                c++;   
            }
        }
    }
    
    printf(" caratteri in comune:");
    
    for(int i = 0; i<lunghezza; i++)
    {
            printf("%c\n", comuni[i]);  
    }
    
    return 0;
}