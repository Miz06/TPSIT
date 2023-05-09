#include <stdio.h>
#include <string.h>
#include <limits.h>
//Alessandro Mizzon  3E
    void Tasto1(int array[], int lung)
    {
        for(int i = 0; i<lung; i++)
        {
            printf("%d\n", array[i]); 
        }
    }

    int Tasto2(int array[], int n, int lung)
    {
        array[lung]=n; 
        return array[lung]; 
    }

    int Tasto3(int array[], int lung, int modificato, int sostituto)
    {
        if(modificato<lung)
        {
            array[modificato]=sostituto; 
            return array[modificato]; 
        }
        else
        {
            printf("La sezione dell'array non contiene alcun valore\n"); 
        }
    }

    int Tasto4(int array[], int lung, int elimina)
    {
        if(elimina<lung)
        {
            for(int j = elimina; j<lung-1; j++)
            {
                array[j] = array[j+1]; 
            } 

            return lung-1; 
        }
        else
        {
            printf("La sezione dell'array non può essere eliminata in quanto non è presente\n"); 
        }

    }

    int Tasto5(int array[], int ricerca, int lung)
    {
        for(int t = 0; t<lung; t++)
        {
            if(array[t]==ricerca)
            {
                return t; 
            }
        }
    }

    int Tasto6(int array[], int lung, int aggiunto, int posizione, int supporto)
    {
        for(int i = lung+1; i>posizione-1; i--)
        {
            array[i]=array[i-1]; 
        }

        array[posizione]=aggiunto; 

        return lung+1; 
    }

    void Tasto7(int array[], int lung)
    {
        for(int i = lung-1; i>-1; i--)
        {
            printf("%d\n", array[i]); 
        }
    }

    void Tasto8(int array[], int lung, int max)
    {
        max = array[0]; 

        for(int i = 0; i<lung-1; i++)
        {
            if(array[i+1]>array[i])
            {
                max = array[i+1]; 
            }
        }

        printf("Il numero più grande è: %d\n", max); 
    }

    int main(int argc, char *argv[])
    {
        int numeri[SHRT_MAX]; 
        int lunghezza = 0, aggiunto, num, f, aggiunti=0, modificato, sostituto, 
        elimina, ricerca, posizione, aggiunto2, posizione2, supporto, max; 

        do
        {
            printf("Inserire un numero:"); 
            scanf("%d", &num); 
                    
            if(num!=-1)
            {
                numeri[lunghezza]=num;  
                lunghezza++;   
            }
                
        }while(num != -1); 

        do
        {   

            printf("-------\n");
            printf("premere 1 per mostrare il contenuto dell'array\n"); 
            printf("premere 2 per inserire un elemento in coda\n");
            printf("premere 3 per modificare un elemento, se presente\n");
            printf("premere 4 per eliminare un elemento, se presente\n");
            printf("premere 5 per ricercare un elemento\n");
            printf("premere 6 per inserire un elemento in una certa posizione\n");
            printf("premere 7 per mostrare il contenuto dell'array all'inverso\n");
            printf("premere 8 per mostrare il valore massimo dell'array\n");
            printf("premere 0 per terminare\n");

            printf("-------\n"); 
            printf("Inserire il numero corrispondente alla funzione che si desidera svolgere:"); 
            scanf("%d", &f);
            printf("-------\n"); 

            if(f == 1)
            {
                Tasto1(numeri, lunghezza); 
            }

            if(f == 2)
            {
                printf("Inserire il numero da inserire in coda:");
                scanf("%d", &aggiunto);
                numeri[lunghezza]=Tasto2(numeri, aggiunto, lunghezza); 
                aggiunti++; 
                lunghezza+=aggiunti; 
            }

            if(f==3)
            {
                printf("Quale posizione si desidera modificare?");
                scanf("%d", &modificato);
                printf("Quale valore si desidera assegnarle?");
                scanf("%d", &sostituto);
                numeri[modificato]=Tasto3(numeri, lunghezza, modificato, sostituto); 
            }
            
            if(f == 4)
            {
                printf("Quale posizione si desidera eliminare?");
                scanf("%d", &elimina);
                lunghezza = Tasto4(numeri, lunghezza, elimina);
            }

            if(f == 5)
            {
                printf("Quale numero si desidera ricercare?");
                scanf("%d", &ricerca);
                posizione = Tasto5(numeri, ricerca, lunghezza); 
                printf("Il numero si trova in posizione: %d", posizione);
            }

            if(f==6)
            {
                printf("Quale elemento si desidera aggiungere?");
                scanf("%d", &aggiunto2);
                printf("In quale posizione?");
                scanf("%d", &posizione2);
                lunghezza = Tasto6(numeri, lunghezza, aggiunto2, posizione2, supporto);
            }

            if(f==7)
            {
                Tasto7(numeri, lunghezza); 
            }

            if(f==8)
            {
                Tasto8(numeri, lunghezza, max); 
            }
        }while(f != 0); 
    }