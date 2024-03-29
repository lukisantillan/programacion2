#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void bombita(int A, int B,int* vec,int *indice){
    int resultado;
    if (A <= B)
    {
        vec[(*indice)++]=B;
    
        return;
    }

    int n1 = A / B;
    int n2 = A - (A/B);

    if (n1 > B)
    {
        resultado = n1;
    } else {
        vec[(*indice)++]=n1;
    
    }
    if (n2 >= B)
    {
        resultado = n2;
    } else {
        vec[(*indice)++]=n2;
        }
    return bombita(resultado, B,vec,indice);

}
int* bomba(int A,int B)
{
int* vec;
int puntero=0;//indice del vector
int max;


max=A/B+1;// calculo la cantidad maxima de elementos
vec=malloc(sizeof(int)*max);//asigno memoria dinamica a un puntero(vector)
bombita(A,B,vec,&puntero);

return vec;

}