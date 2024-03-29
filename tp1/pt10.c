#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//falta hacer que se guarde en un vector
void bomba(int A, int B){
    int resultado;
    if (A <= B)
    {
        printf(" %i", B);
    
        return;
    }

    int n1 = A / B;
    int n2 = A - (A/B);

    if (n1 > B)
    {
        resultado = n1;
    } else {
        printf(" %i", n1);
    
    }
    if (n2 >= B)
    {
        resultado = n2;
    } else {
        printf(" %i", n2);
        }
    return bomba(resultado, B);

}