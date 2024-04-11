#include "ejercicios.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void CompararListas(Lista l1, Lista l2)
{
    int lon1 = l_longitud(l1);
    int lon2 = l_longitud(l2);
    int cantidad = 0;
    TipoElemento eleLis2, elelis1;
    if (lon1 != lon2)
    {
        printf("\n Las longitudes son diferentes");
    }
    else
    {
        for (int i = 1; i <= lon1; i++)
        {
            elelis1 = l_recuperar(l1, i);
            eleLis2 = l_recuperar(l2, i);
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
