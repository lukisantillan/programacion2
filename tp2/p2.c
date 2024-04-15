#include <stdlib.h>
#include <stdio.h>
#include "listas.h"
#include "ejercicios.h"

Lista verElementosRepetidos(Lista l1, Lista l2)
{
    Lista listaRepetidos = l_crear();
    TipoElemento elementoActual, elementoBuscado;
    int longitudLista = l_longitud(l1);
    Iterador itl1 = iterador(l1);
    while (hay_siguiente(itl1))
    {
        elementoActual = siguiente(itl1);
        int clave = elementoActual->clave;
        elementoBuscado = l_buscar(l2, clave);
        if (elementoBuscado != NULL)
        {
            l_agregar(listaRepetidos, elementoBuscado);
        }
    }
    return listaRepetidos;
}

Lista verElementosQueNoSeRepiten(Lista l1, Lista l2)
{
    Lista listaNoRepetidos = l_crear();
    TipoElemento elementoActual, elementoBuscado;
    int longitudLista = l_longitud(l1);
    Iterador itl1 = iterador(l1);
    while (hay_siguiente(itl1))
    {
        elementoActual = siguiente(itl1);
        int clave = elementoActual->clave;
        elementoBuscado = l_buscar(l2, clave);
        if (elementoBuscado == NULL)
        {
            l_agregar(listaNoRepetidos, elementoActual);
        }
    }
    return listaNoRepetidos;
}

float promedio(Lista l1)
{
    int lon1 = l_longitud(l1);
    float suma = 0;
    TipoElemento elementoActual;
    Iterador itl1 = iterador(l1);
    while (hay_siguiente(itl1))
    {
        elementoActual = siguiente(itl1);
        suma += elementoActual->clave;
    }
    printf("\n\t\t suma: %.5f", suma);
    float promedio = suma / lon1;
    return promedio;
}

Resultados promedioAmbasListas(Lista l1, Lista l2)
{
    Resultados resu;
    resu.resultado1 = promedio(l1);
    resu.resultado2 = promedio(l2);
    return resu;
}

ResultadoValorMaximo valorMaximo(Lista l1, Lista l2)
{
    ResultadoValorMaximo resultado;
    resultado.valor = -99999;
    TipoElemento elementoActual;

    // lista 1
    for (int i = 1; i <= l_longitud(l1); i++)
    {
        elementoActual = l_recuperar(l1, i);
        if (elementoActual->clave > resultado.valor)
        {
            resultado.valor = elementoActual->clave;
            resultado.pos = i;
            resultado.lista = 1;
        }
    }

    // lista 2
    for (int i = 1; i <= l_longitud(l2); i++)
    {
        elementoActual = l_recuperar(l2, i);
        if (elementoActual->clave > resultado.valor)
        {
            resultado.valor = elementoActual->clave;
            resultado.pos = i;
            resultado.lista = 2;
        }
    }

    return resultado;
}

// int main()
// {
//     Lista l1 = rellenarLista(3);
//     printf("\nLista2");
//     Lista l2 = rellenarLista(3);
//     ResultadoValorMaximo valorMax = valorMaximo(l1, l2);
//     printf("\nValor maximo: %d", valorMax.valor);
//     printf("\nPosicion: %d", valorMax.pos);
//     printf("\nLista: %d", valorMax.lista);
//     return 0;
// }

// gcc -o output ./tp2/tipo_elemento.c ./tp2/listas_arreglos.c ./tp2/p2.c
// gcc -o output ./tp2/tipo_elemento.c ./tp2/listas_cursores.c ./tp2/p2.c
// gcc -o output ./tp2/tipo_elemento.c ./tp2/listas_punteros.c ./tp2/p2.c