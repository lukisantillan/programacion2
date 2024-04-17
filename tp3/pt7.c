#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../libs/pilas/pilas.h"

Pila p_ej7_eliminarclave(Pila p1, Pila p2)
{
    Pila aux1 = p_crear();
    Pila aux2 = p_crear();
    Pila resultado = p_crear();
    TipoElemento ele1;
    TipoElemento ele2;

    while (!p_es_vacia(p1))
    {
        ele1 = p_desapilar(p1);
        p_apilar(aux1, ele1);
        bool flag = true;
        while (!p_es_vacia(p2) && flag)
        {
            ele2 = p_desapilar(p2);
            p_apilar(aux2, ele2);
            if (ele1->clave == ele2->clave)
            {
                p_apilar(resultado, ele1);
                flag = false;
            }
        }
        while (!p_es_vacia(aux2))
        {
            ele2 = p_desapilar(aux2);
            p_apilar(p2, ele2);
        }
    }
    return resultado;
}
/*
int main()
{
    Pila pila = p_crear();
    rellenarPila(pila, 4);
    Pila pila2 = p_crear();
    rellenarPila(pila2, 4);
    p_mostrar(pila);
    p_mostrar(pila2);
    Pila resultado = p_ej7_eliminarclave(pila, pila2);
    p_mostrar(resultado);
    return 0;
}
*/
