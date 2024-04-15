#include "ejercicios.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Complejidad:
// Algoritmo: O(n)
// Listas cursores: O(n)
// Listas punteros: O(n)
// Listas arreglos: O(n)
void CompararListas(Lista l1, Lista l2)
{
    int lon1 = l_longitud(l1);
    int lon2 = l_longitud(l2);
    int cantidad = 0;
    Iterador itl1 = iterador(l1);
    Iterador itl2 = iterador(l2);
    TipoElemento eleLis2, elelis1;
    if (lon1 != lon2)
    {
        printf("\n Las longitudes son diferentes");
    }
    else
    {
        while(hay_siguiente(itl1))
        {
            elelis1 = siguiente(itl1);
            eleLis2 = siguiente(itl2);
            printf("\n\t\t\t ELE 1: %i / ELE 2: %i", elelis1->clave, eleLis2->clave);
            if (elelis1->clave > eleLis2->clave)
            {
                cantidad++;
            }
            else if (elelis1->clave < eleLis2->clave)
            {
                cantidad--;
            }
        }
        if (cantidad < 0)
        {
            printf("\n Lista 1 es menor que Lista 2");
        }
        else if (cantidad > 0)
        {
            printf("\n Lista 1 es mayor que Lista 2");
        }
        else
        {
            printf("\n Las listas son iguales");
        }
    }
}
/*
int main()
{
    Lista l1 = rellenarLista(3);
    printf("\nLista2");
    Lista l2 = rellenarLista(3);
    CompararListas(l1,l2);
    return 0;
}
*/
// gcc -o output tipo_elemento.c listas_arreglos.c p4.c
// gcc -o output tipo_elemento.c listas_cursores.c p4.c
// gcc -o output tipo_elemento.c listas_punteros.c p4.c