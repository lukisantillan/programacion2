#include <stdio.h>
#include <stdlib.h>

#include "tp_colas.h"
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
    // ENCOLO DE NUEVO
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
        c_encolar(resultado, ele);
        i++;
        if (i == posicionordinal)
        {
            ele = te_crear(elemento);
            c_encolar(resultado, ele); // ENCOLO EL ELEMENTO EN LA POS;
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
    if (!resultB)
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
            if (ele->clave != clave)
            {
                c_encolar(resultado, ele);
            }
        }
        return resultado;
    }
}

int c_ej2_contarelementos(Cola c)
{
    TipoElemento ele;
    Cola aux = c_crear();
    int resultado = 0;
    if (c_es_vacia(c))
    {
        return 0;
    }
    else
    {
        TipoElemento ele = c_desencolar(c);
        int resultado = 1 + c_ej2_contarelementos(c);
        c_encolar(c, ele);
        return resultado;
    }
}

Cola c_ej2_copiar(Cola c)
{
    Cola resultado = c_crear();
    Cola aux = c_crear();
    TipoElemento ele;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        c_encolar(resultado, ele);
        c_encolar(aux, ele);
    }
    // ENCOLO EN LA ORIGINAL
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
    }
    return resultado;
}

Cola c_ej2_invertir(Cola c)
{
    Cola resultado = c_crear();
    Pila invertir = p_crear();
    Cola aux = c_crear();
    TipoElemento ele;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        p_apilar(invertir, ele);
        c_encolar(aux, ele);
    }
    // Invierto
    while (!p_es_vacia(invertir))
    {
        ele = p_desapilar(invertir);
        c_encolar(resultado, ele);
    }
    // Reencolo en cola original
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
    }
    return resultado;
}

// Ejercicio3
bool c_ej3_iguales(Cola c1, Cola c2)
{
    Cola aux = c_crear();
    bool resultado = true;
    TipoElemento ele1, ele2;
      if (c_ej2_contarelementos(c1)!= c_ej2_contarelementos(c2))
    {
        
        return false;
    }
    while (!c_es_vacia(c1))
    {
        ele1 = c_desencolar(c1);
        ele2 = c_desencolar(c2);
        if (ele1->clave != ele2->clave)
        {
            resultado = false;
        }
        c_encolar(aux, ele1);
        c_encolar(aux, ele2);
    }
    // ENCOLO NUEVAMENTE EN LAS COLAS
    while (!c_es_vacia(aux))
    {
        ele1 = c_desencolar(aux);
        ele2 = c_desencolar(aux);
        c_encolar(c1, ele1);
        c_encolar(c2, ele2);
    }
    return resultado;
}

// Ejercicio 4

// Complejidad: O(n)
Cola c_ej4_colanorepetidos(Cola c)
{
    Cola aux = c_crear();
    Cola repetidos = c_crear();
    Cola resultado = c_crear();
    while (!c_es_vacia(c))
    {
        TipoElemento ele = c_desencolar(c);
        c_encolar(aux, ele);
    }
    while (!c_es_vacia(aux))
    {
        TipoElemento ele = c_desencolar(aux);
        c_encolar(c, ele);
        if (c_ej2_existeclave(aux, ele->clave))
        {
            c_encolar(repetidos, ele);
        }
        else if (!c_ej2_existeclave(repetidos, ele->clave))
        {
            c_encolar(resultado, ele);
        }
    }

    return resultado;
}

int main()
{
    Cola c1 = c_crear();
    rellenarCola(c1, 4);
    // printf("EJERCICIO EXISTE CLAVE\n");
    // bool resultado1 = c_ej2_existeclave(c1, 3);
    // if (resultado1)
    // {
    //     printf("Existe la clave en la pila\n");
    // }
    // else
    // {
    //     printf("No existe la clave en la pila\n");
    // }

    Cola c2 = c_ej4_colanorepetidos(c1);
    printf("Cola 1\n");
    c_mostrar(c1);
    printf("Cola de no repetidos\n");
    c_mostrar(c2);

    return 0;
}