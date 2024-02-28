#include <stdio.h>

    int Add(int a){
        int x = 10; //local variable allocated in the STACK
        return a+x; 
    }

int main(){

    int a = 4;

    a = Add(a); //function call for information contained in the STACK
    printf("%d\n", a);

    int *p = (int*)malloc(sizeof(int)); //manual memory allocation
    free(p); //manual memory deallocation
    
    return 0;
}