#include "ejercicios.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Complejidad:
// Algoritmo: O(n)
// Listas cursores: O(n)
// Listas punteros: O(n)
// Listas arreglos: O(n)
ResultadosMul multiplo(Lista l1, Lista l2)
{
    ResultadosMul resultado;
    resultado.esMultiplo = true;
    int lon1 = l_longitud(l1);
    int lon2 = l_longitud(l2);
    TipoElemento eleLis2, Elelis1;
    Iterador itl1 = iterador(l1);
    Iterador itl2 = iterador(l2);
    if (lon1 != lon2)
    {
        resultado.esMultiplo = false;
        resultado.escalar = false;
        return resultado;
    }

    int flagPrimero = 0;
    int escalar;
    while (hay_siguiente(itl1) && resultado.esMultiplo)
    {
        eleLis2 = siguiente(itl2);
        Elelis1 = siguiente(itl1);
        if (eleLis2->clave % Elelis1->clave == 0 &&flagPrimero == 0)
        {
            escalar = eleLis2->clave / Elelis1->clave;
            resultado.escalar = true;
        }
        else if (eleLis2->clave % Elelis1->clave != 0)
        {
            resultado.esMultiplo = false;
        }
        else
        {
            int division = eleLis2->clave / Elelis1->clave;
            if (division != escalar)
            {
                resultado.escalar = false;
            }
        }
    }
    if (resultado.escalar)
    {
        resultado.numEscalar = escalar;
    }
    return resultado;
}

/*
int main()
{
    Lista l1 = rellenarLista(3);
    printf("\nLista2");
    Lista l2 = rellenarLista(4);
    ResultadosMul resultado = multiplo(l1, l2);
    if (!resultado.esMultiplo)
    {
        printf("\n L2 NO ES MULTIPLO DE L1");
    }
    else
    {
        printf("\n L2 ES MULTIPLO DE L1");
        if (resultado.escalar)
        {
            printf("\n Es escalar en el numero %i", resultado.numEscalar);
        }
    }

    return 0;
}
*/

// gcc -o output tipo_elemento.c listas_arreglos.c p3.c
// gcc -o output tipo_elemento.c listas_cursores.c p3.c
// gcc -o output tipo_elemento.c listas_punteros.c p3.c