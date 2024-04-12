#include "ejercicios.h"
#include <stdlib.h>
#include <stdio.h>


Lista verElementosRepetidos(Lista l1, Lista l2)
{
    Lista listaRepetidos = l_crear();
    TipoElemento elementoActual, elementoBuscado;
    int longitudLista = l_longitud(l1);
    Iterador itl1 = iterador(l1);
    while(hay_siguiente(itl1))
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
    while(hay_siguiente(itl1))
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

float promedio(Lista l1){
    int lon1 = l_longitud(l1);
    float suma = 0;
    TipoElemento elementoActual;
    Iterador itl1 = iterador(l1);
    while(hay_siguiente(itl1))
    {
        elementoActual=siguiente(itl1);
        suma+=elementoActual->clave;
    }
    printf("\n\t\t suma: %.5f", suma);
    float promedio =  suma / lon1;
    return promedio;
}

Resultados promedioAmbasListas(Lista l1, Lista l2){
    Resultados resu;
    resu.resultado1 = promedio(l1);
    resu.resultado2= promedio(l2);
    return resu;
}

int valormaximo(Lista l, int *posicion){
    int valormax=0;//guardo para comparar
    int longitudlista= l_longitud(l);//guardo longitud para el for
    TipoElemento elementoactual;//elemento va a tener clave y valor
    for (int i=1;i<=longitudlista;i++){
        elementoactual=l_recuperar(l,i);//elementoactual va a tener un puntero al elem.lista[i]
        if(elementoactual->clave >valormax){
            valormax=elementoactual->clave;
            *posicion=i;
        }
    }
    
    return valormax;
}

//FALTA ARREGLAR LA DE VALOR MAXIMO PORQUE NO SE ME OCURRE FORMA DE ENCONTRAR POSICION

/*
int main()
{
    Lista l1 = rellenarLista(3);
    printf("\nLista2");
    Lista l2 = rellenarLista(3);
    Lista resultado = verElementosRepetidos(l1,l2);
    l_mostrar(resultado);
    return 0;
}
*/

// gcc -o output tipo_elemento.c listas_arreglos.c p2.c
// gcc -o output tipo_elemento.c listas_cursores.c p2.c
// gcc -o output tipo_elemento.c listas_punteros.c p2.c