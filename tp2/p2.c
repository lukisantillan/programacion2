#include <stdlib.h>
#include <stdio.h>

#include "./TP_2_Listas.h"

/*
    Ejercicio 2.
    *   Dada una 2 listas (L1 y L2) cargadas con valores al azar (en la clave) realizar los siguientes
        ejercicios:
            a. Que retorne una lista con los valores de L1 que no están en L2.
            b. Que retorne una lista con los valores de L2 que no están en L1.
            c. Que retorne una lista con todos los valores comunes a ambas listas (L1 y L2).
            d. Que retorne los promedios de ambas listas.
            e. Que retorne el valor máximo de ambas listas y su posición ordinal.

    Compilación:
    *   gcc -o p2.output ./p2.c ./listas_punteros.c ./tipo_elemento.c && ./p2.output
        gcc -o p2.output ./p2.c ./listas_cursores.c ./tipo_elemento.c && ./p2.output
        gcc -o p2.output ./p2.c ./listas_arreglos.c ./tipo_elemento.c && ./p2.output
*/

/*
 * Retorna una lista con los valores de L1 que están en L2.
 * @param Lista l1: Lista 1.
 * @param Lista l2: Lista 2.
 * @return Lista: Lista con los valores de L1 que están en L2.
 * Complejidad algoritmica: O(n)
 * Complejidad algoritmica en listas arreglo: O(n^2)
 * Complejidad algoritmica en listas cursores: O(n^3)
 * Complejidad algoritmica en listas punteros: O(n^3)
 */
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

/*
 * Retorna una lista con los valores de L2 que no están en L1.
 * @param Lista l1: Lista 1.
 * @param Lista l2: Lista 2.
 * @return Lista: Lista con los valores de L2 que no están en L1.
 * Complejidad algoritmica: O(n)
 * Complejidad algoritmica en listas arreglo: O(n^2)
 * Complejidad algoritmica en listas cursores: O(n^3)
 * Complejidad algoritmica en listas punteros: O(n^3)
 */
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

/*
 * Retora el promedio de una lista.
 * @param Lista l1: Lista.
 * @return float: Promedio de la lista.
 * Complejidad algoritmica: O(n)
 */
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
    float promedio = suma / lon1;
    return promedio;
}

/*
 * Retorna el promedio de ambas listas.
 * @param Lista l1: Lista 1.
 * @param Lista l2: Lista 2.
 * @return Resultados: Resultados de los promedios.
 * Complejidad algoritmica: O(n+m)
 * Complejidad algoritmica en listas arreglo: O(n+m)
 * Complejidad algoritmica en listas cursores: O(n+m)
 * Complejidad algoritmica en listas punteros: O(n+m)
 */
Resultados promedioAmbasListas(Lista l1, Lista l2)
{
    Resultados resu;
    resu.resultado1 = promedio(l1);
    resu.resultado2 = promedio(l2);
    return resu;
}

/*
 * Retorna el valor máximo de ambas listas y su posición ordinal.
 * @param Lista l1: Lista 1.
 * @param Lista l2: Lista 2.
 * @return ResultadoValorMaximo: Resultado del valor máximo.
 * Complejidad algoritmica: O(n+m)
 * Complejidad algoritmica en listas arreglo: O(n+m)
 * Complejidad algoritmica en listas cursores: O(n^2 + m^2)
 * Complejidad algoritmica en listas punteros: O(n^2 + m^2)
 */
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