#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int p; /* gestisce il padre e il figlio
        p padre = p figlio = 0*/

int main()
{
    //fork() crea una copia del codice
    p = fork(); //da qui ho due main uguali in memoria nonchè due processi ma con due PID diversi (codice fiscale per processi)
    //la fork è lanciata dal padre e genera un figlio
    //si utilizza per smezzare i tempi di esecuzione del processo
    //tutti i processi hanno un padre tranne il processo init che è il primo processo ad essere lanciato (dal kernel)

    if(p>0)
    {
        printf("Processo padre    p = %d, PID=%d, mio padre ha PID=%d", p, getpid(), getppid());

    }
    else
    {
        printf("Processo figlio    p = %d, PID=%d, mio padre ha PID=%d", p, getpid(), getppid());
    }

    return 0;
}

