#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../libs/pilas/pilas.h"

Pila p_ej5_invertir(Pila p)
{
    Pila aux = p_crear();
    Pila invertida = p_crear();
    TipoElemento ele;
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
        p_apilar(invertida, ele);
    }
    // REAPILO PARA NO PERDER ORIGINAL
    while (!p_es_vacia(aux))
    {
        ele = p_desapilar(aux);
        p_apilar(p, ele);
    }
    return invertida;
}