#include <stdio.h>
void main()
{
    /*Progettare un algoritmo che effettui le seguenti operazioni:
    • continui a leggere da tastiera due valori numerici, fermandosi quando uno dei due numeri è 0 (zero)
    • per ogni coppia di numeri letti:
    • calcoli il prodotto dei due numeri e ne stampi il valore
    • sommi il prodotto calcolato ad una variabile che memorizzi la somma di tutti i prodotti
    • all’uscita del ciclo, stampi il valore della somma*/

    int val1, val2, prodotto = 0, somma = 0;

    do
    {
        printf("Inserire il valore 1:\n");
        scanf("%d", &val1);

        printf("Inserire il valore 2:\n");
        scanf("%d", &val2);

        prodotto = val1 * val2;
        somma = somma + prodotto;

        printf("Il prodotto dei due valori inseriti è: %d\n", prodotto);

    } while (val1 != 0 && val2 != 0);

    printf("La somma dei due valori inseriti è: %d\n", somma);
}