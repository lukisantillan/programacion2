#include "ejercicios.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


Lista verElementosRepetidos(Lista l1, Lista l2)
{
    Lista listaRepetidos = l_crear();
    TipoElemento elementoActual, elementoBuscado;
    int longitudLista = l_longitud(l1);
    for (int i = 1; i <= longitudLista; i++)
    {
        elementoActual = l_recuperar(l1, i);
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
    for (int i = 1; i <= longitudLista; i++)
    {
        elementoActual = l_recuperar(l1, i);
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
    for (int i = 1; i <= lon1; i++)
    {
        elementoActual=l_recuperar(l1, i);
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

Lista rellenarLista(int elementos)
{
    Lista l = l_crear();
    TipoElemento x;
    srand(time(NULL));
    bool blAg = true;
    for (int i = 0; i < elementos; i++)
    {
        int numero_aleatorio;
        printf("\n Ingrese el numero a agregar en la lista: ");
        scanf("%i", &numero_aleatorio);
        x = te_crear(numero_aleatorio);
        blAg = blAg && l_agregar(l, x);
    }
    if (!blAg)
    {
        l = l_crear();
    }
    return l;
}

