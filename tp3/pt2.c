#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tp_pilas.h"

void rellenarPila(Pila pila, int cantidadDeElementos)
{
    TipoElemento elemento;
    int clave;
    for (int i = 0; i < cantidadDeElementos; i++)
    {
        printf("Ingrese la clave:   \n");
        scanf("%d", &clave);
        elemento = te_crear(clave);
        p_apilar(pila, elemento);
    }
}

bool p_ej2_existeclave(Pila p, int clave)
{
    bool resultado = false;
    Pila aux = p_crear();
    TipoElemento ele;
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        if (ele->clave == clave)
        {
            resultado = true;
        }
        p_apilar(aux, ele);
    }

    // RECOMPONGO LA PILA INGRESADA
    while (!p_es_vacia(aux))
    {

        ele = p_desapilar(aux);
        p_apilar(p, ele);
    }

    return resultado;
}

Pila p_ej2_colocarelemento(Pila p, int posicionordinal)
{
    Pila aux = p_crear();
    Pila resultado = p_crear();
    TipoElemento ele;
    int i = 0, elemento;
    // Desapilo
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
    }
    // SOLICITO EL ELEMENTO A AGREGAR EN LA PILA
    printf("Ingrese el elemento que desea agregar:  \n");
    scanf("%d", &elemento);
    // Reapilo, para en el resultado poder agregar el elemento
    while (!p_es_vacia(aux))
    {
        ele = p_desapilar(aux);
        p_apilar(p, ele);
        p_apilar(resultado, ele);
        i++;
        if (i == posicionordinal)
        {
            ele = te_crear(elemento);
            p_apilar(resultado, ele); // Agrego el elemento al resultado;
        }
    }

    return resultado;
}

Pila p_ej2_eliminarclave(Pila p, int clave)
{
    bool resulBusqueda = p_ej2_existeclave(p,clave);
    Pila resultado = p_crear();
    Pila aux= p_crear();
    TipoElemento ele;
    if (!resulBusqueda)
    {
        return p;
    }
    else
    {
        while (!p_es_vacia(p))
        {
            ele = p_desapilar(p);
            p_apilar(aux, ele);
        }

        // Reapilo, para en el resultado poder quitar el elemento
        while (!p_es_vacia(aux))
        {
            ele = p_desapilar(aux);
            p_apilar(p, ele); // Linea para conservar pila original
            //Siempre que el elemento sea distinto a la clave, lo apilamos en el resultado;
            if (ele->clave != clave)
            {
                p_apilar(resultado, ele);
            }
        }
        return resultado;
    }
}

//FALTA HACER QUE LO DUPLIQUE ORDENADO

Pila p_ej2_duplicar(Pila p){
    Pila resultado = p_crear();
    Pila aux= p_crear();
    TipoElemento ele;
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
    }

    while (!p_es_vacia(aux))
    {

        ele = p_desapilar(aux);
        p_apilar(p, ele);
        p_apilar(resultado,ele);
    }
    return resultado;
}
int main()
{
    Pila pila = p_crear();
    rellenarPila(pila, 3);
    p_mostrar(pila);
    Pila resultado = p_ej2_duplicar(pila);
    p_mostrar(resultado);
    p_mostrar(pila);

    /*
    bool resultado = p_ej2_existeclave(pila, 23);
    if (resultado)
    {
        printf("Existe la clave en la pila\n");
    } else {printf("No existe la clave en la pila\n");}
    p_mostrar(pila);
    p_mostrar(pila);
    Pila resultado =  p_ej2_colocarelemento(pila, 3);
    p_mostrar(pila);
    p_mostrar(resultado);
     */
    return 0;
}
