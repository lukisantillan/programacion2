#include "ejercicios.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

ResultadosMul multiplo(Lista l1, Lista l2)
{
    ResultadosMul resultado;
    resultado.esMultiplo = true;
    int lon1 = l_longitud(l1);
    int lon2 = l_longitud(l2);
    TipoElemento eleLis2, Elelis1;
    int i = 1;
    if (lon1 != lon2)
    {
        resultado.esMultiplo = false;
        resultado.escalar = false;
        return resultado;
    }

    int flagPrimero = 0;
    int escalar;
    while (i != lon1 && resultado.esMultiplo)
    {
        eleLis2 = l_recuperar(l2, i);
        Elelis1 = l_recuperar(l1, i);
        if (eleLis2->clave % Elelis1->clave == 0 &&flagPrimero == 0)
        {
            escalar = eleLis2->clave / Elelis1->clave;
            resultado.escalar = true;
            i++;
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
            i++;
        }
    }
    if (resultado.escalar)
    {
        resultado.numEscalar = escalar;
    }
    return resultado;
}

int main()
{
    Lista l1 = rellenarLista(3);
    printf("\nLista2");
    Lista l2 = rellenarLista(3);
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
