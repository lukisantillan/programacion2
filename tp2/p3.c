#include "ejercicios.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
    Ejercicio 3.
    *   Dadas 2 listas (L1 y L2) determinar si L2 es múltiplo de L1.  Se considera múltiplo si cada
        elemento de L2 se divide en forma exacta por el valor L1 de la misma posición.   Usar la
        clave como campo de datos solamente.
            Ejemplo: si L1 = (2, 5, 7, 3) y L2 = (8, 20, 28, 12) entonces L2 es múltiplo por L1 porque
            cada posición de L2 se divide por el valor de L1 de la misma posición en forma exacta
            (sin decimales). Si el resultado de la división retorna el mismo valor para cada posición
            se dice que “L2” es múltiplo de “L1” por un “escalar”.  Para este caso “4” es el escalar
            de L1.  El algoritmo debe contemplar esta situación.

    Compilación:
    *   gcc -o p3.output ./p3.c ./listas_punteros.c ./tipo_elemento.c && ./p3.output
        gcc -o p3.output ./p3.c ./listas_cursores.c ./tipo_elemento.c && ./p3.output
        gcc -o p3.output ./p3.c ./listas_arreglos.c ./tipo_elemento.c && ./p3.output
*/

/*
 * Determina si L2 es múltiplo de L1.
 * @param Lista l1: Lista 1.
 * @param Lista l2: Lista 2.
 * @return ResultadosMul: Resultados de la operación.
 * Complejidad algoritmica: O(n)
 */
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
        if (eleLis2->clave % Elelis1->clave == 0 && flagPrimero == 0)
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