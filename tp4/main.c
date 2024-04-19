#include <stdio.h>
#include <stdlib.h>

#include "../libs/colas/colas.h"
#include "../libs/elementos/tipo_elemento.h"
// Funciónes Extras

void rellenarCola(Cola cola, int cantidadDeElementos)
{
    TipoElemento elemento;
    int clave;
    for (int i = 0; i < cantidadDeElementos; i++)
    {
        printf("Ingrese la clave:   \n");
        scanf("%d", &clave);
        elemento = te_crear(clave);
        c_encolar(cola, elemento);
    }
}
// Ejercicio2
bool c_ej2_existeclave(Cola c, int clave)
{
    Cola aux = c_crear();
    bool resultado = false;
    TipoElemento ele;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        if (ele->clave == clave)
        {
            resultado = true;
        }
        c_encolar(aux, ele);
    }
    // ENCOLO DE NUEVO
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
    }
    return resultado;
}

Cola c_ej2_colarelemento(Cola c, int posicionordinal)
{
    Cola aux = c_crear();
    Cola resultado = c_crear();
    TipoElemento ele;
    int elemento;
    int i = 1;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        c_encolar(aux, ele);
    }
    //ENCOLO DE NUEVO
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
        c_encolar(resultado, ele);
        i++;
        if (i == posicionordinal)
        {
            ele = te_crear(elemento);
            c_encolar(resultado, ele); //ENCOLO EL ELEMENTO EN LA POS;
        }
    }
    return resultado;
}

Cola c_ej2_sacarelemento(Cola c, int clave)
{
    bool resultB = c_ej2_existeclave(c, clave);
    Cola resultado = c_crear();
    Cola aux = c_crear();
    TipoElemento ele;
    if (!resulB)
    {
        return c;
    }
    else
    {
        while (!c_es_vacia(c))
        {
            ele = c_desencolar(c);
            c_encolar(aux, ele);
        }

        // Reencolo, para en el resultado poder quitar el elemento
        while (!c_es_vacia(aux))
        {
            ele = c_desencolar(aux);
            c_encolar(c, ele); 
            // Siempre que el elemento sea distinto a la clave, lo encolamos en el resultado;
            if (ele->clave != clave}
            {
                c_encolar(resultado, ele);
            }
        }
        return resultado;
    }


int main()
{
    Cola c1 = c_crear();
    rellenarCola(c1, 5);
    printf("EJERCICIO EXISTE CLAVE\n");
    bool resultado1 = c_ej2_existeclave(c1, 3);
    if (resultado1)
    {
        printf("Existe la clave en la pila\n");
    }
    else
    {
        printf("No existe la clave en la pila\n");
    }
    return 0;
}