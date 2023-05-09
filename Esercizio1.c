#include <stdio.h>
void main()
{

   /*Esercizio 1
   Progettare un algoritmo che effettui la lettura da tastiera di una serie di coppie di valori numerici.
   L’algoritmo deve calcolare e stampare il rapporto tra il valore minore e quello maggiore dei due. Il
   programma termina quando uno dei due valori o entrambi sono uguali a zero.*/

   int N, N1;
   double rapporto = 0;

   do
   {
      printf("Inserire un numero intero:\n");
      scanf("%d", &N);

      printf("Inserire un numero intero:\n");
      scanf("%d", &N1);

      if (N < N1)
      {
         rapporto = (double)N / (double)N1;
      }
      else
      {
         rapporto = (double)N1 / (double)N;
      }

      printf("Il rapporto tra i due numeri è: %f\n", rapporto);
   } while (N1 != 0 && N1 != 0);
}