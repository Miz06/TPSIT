#include <stdio.h>
/// @brief //add of two numbers
/// @param a //input first number  
/// @param b //input second number
/// @return //return add
int add(int a, int b) //somma 
{
    return a+b;
}
/// @brief //mul of two numbers
/// @param a //input first number 
/// @param b //input second number 
/// @return //return the moltiplication
int mul(int a, int b) //moltiplicazione
{
    return a*b;
}
/// @brief //sub between two numbers 
/// @param a //input first number 
/// @param b //input second number 
/// @return //return sub of two numbers
int sub (int a, int b) //sottrazione
{
    return a-b;
}
/// @brief division between two numbers 
/// @param a //input first number 
/// @param b //input second number 
/// @return //return division between two numbers 
double division(int a, int b) //divisione
{
    return a/b;
}
/// @brief //main function 
void main(){ //main che richiama i metodi
    printf("%d\n",add(6,3));
    printf("%d\n",mul(6,3));
    printf("%d\n",sub(6,3));
    printf("%f\n",division(6,3));
}
