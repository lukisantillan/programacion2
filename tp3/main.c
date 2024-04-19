#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../libs/pilas/pilas.h"
#include "./TP_3_Pilas.h"

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

// Ejercicio2
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
    int i = 1, elemento;
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
    bool resulBusqueda = p_ej2_existeclave(p, clave);
    Pila resultado = p_crear();
    Pila aux = p_crear();
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
        bool flag = true; // flag para que sea solo en la primer ocurrencia;
        while (!p_es_vacia(aux))
        {
            ele = p_desapilar(aux);
            p_apilar(p, ele); // Linea para conservar pila original
            // Siempre que el elemento sea distinto a la clave, lo apilamos en el resultado;
            if (ele->clave == clave && flag)
            {
                flag = false;
            }
            else
            {
                p_apilar(resultado, ele);
            }
        }
        return resultado;
    }
}

Pila p_ej2_duplicar(Pila p)
{
    Pila resultado = p_crear();
    Pila aux = p_crear();
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
        p_apilar(resultado, ele);
        p_apilar(resultado, ele);
    }

    return resultado;
}

Pila p_ej2_intercambiarposiciones(Pila p, int pos1, int pos2)
{
    Pila aux = p_crear();
    Pila resultado = p_crear();
    TipoElemento ele;
    TipoElemento ele1;
    TipoElemento ele2;
    int i = 1;
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
        if (i == pos1)
        {
            ele1 = ele;
        }
        else if (i == pos2)
        {
            ele2 = ele;
        }
        i++;
    }
    while (!p_es_vacia(aux))
    {
        ele = p_desapilar(aux);
        p_apilar(p, ele);
        if (ele->clave == ele2->clave)
        {
            p_apilar(resultado, ele1);
        }
        else if (ele->clave == ele1->clave)
        {
            p_apilar(resultado, ele2);
        }
        else
        {
            p_apilar(resultado, ele);
        }
    }

    return resultado;
}

int p_ej2_cantidadelementos(Pila p)
{
    Pila aux = p_crear();
    int acumulador = 0;
    TipoElemento ele;
    // DESAPILO PARA SABER CUANTOS ELEMENTOS TIENE LA PILA
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
        acumulador++;
    }
    // RELLENO PILA NUEVAMENTE PARA NO PERDERLA
    while (!p_es_vacia(aux))
    {
        ele = p_desapilar(aux);
        p_apilar(p, ele);
    }
    return acumulador;
}

// Ejercicio 3
bool p_ej3_iguales(Pila p1, Pila p2)
{
    Pila aux = p_crear();
    TipoElemento ele1, ele2;
    bool resultado = true;
    while (!p_es_vacia(p1) && !p_es_vacia(p2) && resultado)
    {
        ele1 = p_desapilar(p1);
        ele2 = p_desapilar(p2);
        p_apilar(aux, ele1);
        p_apilar(aux, ele2);
        if (ele1->clave != ele2->clave)
        {
            resultado = false;
        }
    }
    // Hago otro ciclo para reapilar lo que saque de las pilas originales.
    while (!p_es_vacia(aux))
    {
        ele1 = p_desapilar(aux);
        ele2 = p_desapilar(aux);
        p_apilar(p2, ele1);
        p_apilar(p1, ele2);
    }
    return resultado;
}

// Ejercicio 5
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

// Ejercicio 6
Pila p_ej6_eliminarclave(Pila p, int clave)
{
    bool resulBusqueda = p_ej2_existeclave(p, clave);
    Pila resultado = p_crear();
    Pila aux = p_crear();
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
            // Siempre que el elemento sea distinto a la clave, lo apilamos en el resultado;
            if (ele->clave != clave)
            {
                p_apilar(resultado, ele);
            }
        }
        return resultado;
    }
}

// Ejercicio7
Pila p_ej7_elementoscomunes(Pila p1, Pila p2)
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
            }
        }
        // APILO LO QUE DESAPILE, PARA QUE EL SIGUIENTE ELEMENTO PUEDA COMPARARSE
        while (!p_es_vacia(aux2))
        {
            ele2 = p_desapilar(aux2);
            p_apilar(p2, ele2);
        }
    }
    // APILO NUEVAMENTE EN P1 PARA NO PERDERLA.
    while (p_es_vacia(aux1))
    {
        ele1 = p_desapilar(aux1);
        p_apilar(p1, ele1);
    }

    return resultado;
}

int main()
{
    printf("Archivo compilado exitosamente\n");
    printf("Para ejecutar los ejercicios, descomentar las lineas de codigo en el main\n");
    printf("Esto es unicamente para comprobar que la compilacion fue exitosa\n");
    // Pila pila = p_crear();
    // Pila pila2 = p_crear();
    // rellenarPila(pila, 4);
    // printf("----------------------\n");
    // rellenarPila(pila2, 4);
    // printf("\t------------------------------\n");
    // printf("\t ----- PILA PRINCIPAL ----\n");
    // p_mostrar(pila);
    // printf("\t------------------------------\n");
    // printf("EJERCICIO INTERCAMBIAR POSICIONES\n");
    // Pila resultado1 = p_ej2_intercambiarposiciones(pila, 2, 4);
    // p_mostrar(resultado1);
    // printf("------------------------------\n");
    // printf("EJERCICIO EXISTE CLAVE\n");
    // bool resultado2 = p_ej2_existeclave(pila, 3);
    // if (resultado2)
    // {
    //     printf("Existe la clave en la pila\n");
    // } else {printf("No existe la clave en la pila\n");}
    // printf("------------------------------\n");
    // printf("EJERCICIO COLOCAR CLAVE\n");
    // Pila resultado3 =  p_ej2_colocarelemento(pila, 3);
    // p_mostrar(resultado3);
    // printf("------------------------------\n");
    // printf("EJERCICIO ELIMINAR CLAVE\n");
    // Pila resultado4 = p_ej2_eliminarclave(pila, 3);
    // p_mostrar(resultado4);
    // printf("------------------------------\n");
    // printf("EJERCICIO DUPLICAR PILA\n");
    // Pila resultado5 = p_ej2_duplicar(pila);
    // p_mostrar(resultado5);
    // printf("------------------------------\n");
    // printf("EJERCICIO CANTIDAD ELEMENTOS\n");
    // int resultado6 = p_ej2_cantidadelementos(pila);
    // printf("La pila tiene %d elementos\n", resultado6);

    // printf("------------------------------\n");
    // printf("EJERCICIO 3 - LISTAS IGUALES\n");
    // bool resultadoPt3 = p_ej3_iguales(pila, pila2);
    // if (resultadoPt3)
    // {
    //     printf("LAS LISTAS SON IGUALES\n");
    // } else {printf("LAS LISTAS SON DIFERENTES\n");}
    // printf("\t\t- Como quedan las pilas originales despues del retorno -\n");
    // printf("\t\t\t PILA 1\n");
    // p_mostrar(pila);
    // printf("\t\t\t PILA 2\n");
    // p_mostrar(pila2);
    // printf("------------------------------\n");
    // printf("EJERCICIO 5 - INVERTIR\n");
    // Pila resultadoPt5 = p_ej5_invertir(pila);
    // p_mostrar(resultadoPt5);
    // printf("\t\t- Como queda pila oriignal despues del retorno -\n");
    // p_mostrar(pila);
    // printf("------------------------------\n");
    // printf("EJERCICIO 7 - ELEMENTOS COMUNES\n");
    // Pila resultadoPt7 = p_ej7_elementoscomunes(pila,pila2);
    // p_mostrar(resultadoPt7);

    return 0;
}