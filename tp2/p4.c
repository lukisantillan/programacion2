#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "./TP_2_Listas.h"

/*
    Ejercicio 4.
    *   Dadas dos listas L1 y L2, se pide compararlas siempre en el sentido L1L2. Por lo tanto
        puede suceder que:  L1 > L2, L1 = L2 o L1 < L2.   La forma de obtener la comparación es por
        la clave, posición a posición, donde si L1 tiene más cantidad de claves mayores que L2 se
        considera L1 > L2, por el contrario se considera L1 < L2, o de lo contrario L1 será igual a L2.
        Determinar la complejidad algorítmica de la solución empleada.

    Compilación:
    *   gcc -o p4.output ./p4.c ./listas_punteros.c ./tipo_elemento.c && ./p4.output
        gcc -o p4.output ./p4.c ./listas_cursores.c ./tipo_elemento.c && ./p4.output
        gcc -o p4.output ./p4.c ./listas_arreglos.c ./tipo_elemento.c && ./p4.output
*/

/*
 * Compara dos listas.
 * @param Lista l1: Lista 1.
 * @param Lista l2: Lista 2.
 * Complejidad algoritmica: O(n)
 */
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
        while (hay_siguiente(itl1))
        {
            elelis1 = siguiente(itl1);
            eleLis2 = siguiente(itl2);
            printf("\n ELE 1: %i / ELE 2: %i", elelis1->clave, eleLis2->clave);
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