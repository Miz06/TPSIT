#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define BUFFER_DIM 1024

int main(int argc, char*argv[]) {

    typedef struct {
        char name[20];
        char lastname[20];
        int  gradePointAverage;

    } student;

    student class[3];

    strcpy(class[0].name,"name1");
    strcpy(class[0].lastname,"lastname1");
    class[0].gradePointAverage=8;

    strcpy(class[1].name,"name2");
    strcpy(class[1].lastname,"lastname2");
    class[1].gradePointAverage=9;

    strcpy(class[2].name,"name3");
    strcpy(class[2].lastname,"lastname3");
    class[2].gradePointAverage=10;


    FILE *contieneStudenti;
    contieneStudenti = fopen(argv[1],"w+");
    if(contieneStudenti==NULL){
        printf("errore apertura file destinazione %s",argv[1]);
        return 0;        
    }
   
   fwrite(class,sizeof(student),3,contieneStudenti);
   student secondClass[3];
   fread(secondClass,sizeof(student),3,contieneStudenti);
   for(int i=0; i<3; i++){
    printf("%s\n",secondClass[i].name);
    printf("%s\n",secondClass[i].lastname);
    printf("%d\n",secondClass[i].gradePointAverage);
   }

   printf("------------------------\n");
    fseek(contieneStudenti,sizeof(student)*2,SEEK_SET);
    student stud;
    fread(&stud,sizeof(student),3,contieneStudenti);
    printf("%s\n",stud.name);
    printf("%s\n",stud.lastname);
    printf("%d\n",stud.gradePointAverage);
   
  
    fclose(contieneStudenti);
}