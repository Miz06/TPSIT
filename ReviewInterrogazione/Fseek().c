#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *file = fopen("lello.txt", "w");

    fprintf(file, "%s", "ciao");

    fseek(file, 0, SEEK_SET); //serve a settare il puntatore a distanza 0 dall'inizio del file
    fprintf(file, "%s", "A");

    fseek(file, 0, SEEK_END); //serve a settare il puntatore a distanza 0 dalla fine del file
    fprintf(file, "%s", "B");

    fseek(file, -2, SEEK_CUR); //serve a settare il puntatore a distanza 0 dalla posizione corrente del puntatore
    fprintf(file, "%s", "C");
    return 0;
}