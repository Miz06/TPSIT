#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void popolaArray(int vett[], int len)
{
    for (int i = 0; i < len; i++)
    {
        vett[i] = rand() % 30;
    }
}

void stampaArray(int vett[], int len)
{ //1
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d) %d\n", i, vett[i]);
    }
}

void stampaArrayInverso(int vett[], int len)
{ //2
    printf("\n");
    for (int i = len-1; i > -1; i--)
    {
        printf("%d) %d\n", i, vett[i]);
    }
}

int somma(int vett[], int len)
{//3
    int somma = 0;

    for(int i = 0; i<len; i++){
        somma += vett[i];
    }

    return somma;
}

double media(int somma)
{//3
    return     (double)somma/10;
}

void stampaPari(int vett[], int len)
{//4
    for(int i = 0; i<len; i++)
    {
        if(vett[i] % 2 == 0){
            printf("%d\n", vett[i]);
        }
    }
}

void stampaDispari(int vett[],int len)
{//5
    for(int i = 0; i<len; i++)
    {
        if(vett[i] % 2 != 0){
            printf("%d\n", vett[i]);
        }
    }
}

int cercaNum(int vett[], int num, int len)
{//6
    int found = -1; 

<<<<<<< HEAD
    for(int i = 0; i<sizeof(vett); i++){
=======
    for(int i = 0; i<len; i++){
>>>>>>> refs/remotes/origin/main
        if(num == vett[i]){
            found = i;
            i = len;
        }
    }

    return found;
}

<<<<<<< HEAD
void ordinaDispariPari(int vett[]){
    int lenght = sizeof(vett)/sizeof(vett[0]);
    int var;

    if(lenght % 2 == 0)
    {
        for(int i = 0; i<lenght; i+=2){
            var = vett[i];
            vett[i] == vett[i+1];
=======
int rimuoviElemento(int vett[], int num, int len)
{//7
    int found;
    
    found = cercaNum(vett, num, len); 
 
    if(found != -1)
    {
        for(int i =found; i<len-1; i++)
        {
            vett[i] = vett[i+1];
        }
        
        vett[len-1] = -1;
    }
    
    return found;
}

void invertiCoppie(int vett[], int len)
{//8
    int sup;
    
    if(len % 2 == 0)
    {
        for(int i = 0; i<len; i+=2)
        {
            sup = vett[i];
            vett[i] = vett[i+1];
            vett[i+1] = sup;
>>>>>>> refs/remotes/origin/main
        }
    }
    else
    {
<<<<<<< HEAD
        for(int i = 0; i<lenght; i+=2){
            var = vett[i];
            vett[i] == vett[i+1];
=======
        for(int i = 0; i<len-1; i+=2)
        {
            sup = vett[i];
            vett[i] = vett[i+1];
            vett[i+1] = sup;
>>>>>>> refs/remotes/origin/main
        }
    }
}

<<<<<<< HEAD
int main()
{
    int grandezzaArr;
=======
void bubleSort(int vett[], int len)
{
    int sup;
    
    for(int i = 0; i<len; i++)
    {
        for(int j = 0; j<len; j++)
        {
            if(vett[i] > vett[j])
            {
                sup = vett[j];
                vett[j] = vett[i];
                vett[i] = sup;
            }
        }
    }
}
int main()
{
    int len = 9; 
    int arr[10];
    srand(time(0));
>>>>>>> refs/remotes/origin/main
    int choice;
    srand(time(0));

    printf("Grandezza array: ");
    scanf("%d", &grandezzaArr);

<<<<<<< HEAD
    int arr[grandezzaArr];
    popolaArray(arr);
=======
    popolaArray(arr, len);
>>>>>>> refs/remotes/origin/main

    do
    {
        printf("\n-----------------------------\n");
        printf("[1] Visualizza array\n");
        printf("[2] Visualizza ordinamento opposto\n");
        printf("[3] Somma e media\n");
        printf("[4] Visualizza numeri pari\n");
        printf("[5] Visualizza numeri dispari\n");
        printf("[6] Ricerca numero\n");
        printf("[7] Elimina elemento\n");
        printf("[8] Inverti ordine a coppie\n");
        printf("[9] Buble sort\n");
        printf("Scelta: ");
        scanf("%d", &choice);

        if (choice != 0)
        {
            if (choice == 1)
            {
                stampaArray(arr, len);
            }
            else if (choice == 2)
            {
                stampaArrayInverso(arr, len);
            }
            else if(choice == 3)
            {
                int Somma = somma(arr, len);
                printf("\nSomma: %d\n", Somma);
                printf("Media: %f\n", media(Somma));
            }
            else if(choice == 4)
            {
                printf("\n");
                stampaPari(arr, len);
            }
            else if(choice == 5){
                printf("\n");
                stampaDispari(arr, len);
            }
            else if(choice == 6){
                int numRicerca; 

                printf("\nNumero che si desidera ricercare: ");
                scanf("%d", &numRicerca);

                int position = cercaNum(arr, numRicerca, len);

                if(position == -1)
                {
                    printf("Numero non presente nell'array\n");
                }
                else{
                    printf("Il numero si trova in posizione %d\n", position);
                }  
            }
            else if(choice == 7)
            {
                int num; 
                
                printf("\nNumero da rimuovere: ");
                scanf("%d", &num);
                
                if (rimuoviElemento(arr, num, len) != -1)
                {
                    len--;
                }
                else{
                    printf("Numero non presente nell'array\n");
                }
            }
            else if(choice == 8)
            {
                invertiCoppie(arr, len);
            }
            else if(choice == 9)
            {
                bubleSort(arr, len);
                stampaArray(arr, len);
            }
        }
    } while (choice != 0);

    return 0;
}