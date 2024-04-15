#include <stdio.h>
#include <stdlib.h>
#include "tipo_elemento.h"
#include "pilas.h"

Pila RetornarClavesPares(Pila p);
bool EsPilaOrdenada(Pila P);


void main()
{
    int i = 0;
    TipoElemento X;
    Pila P;
    P = p_crear();

    // Mandamos 3 elementos de prepo
    printf("Lenamos la pila con valores <1 a n> de prepo \n");
    while (p_es_llena(P) != true) {
        i = i + 1;
        X = te_crear(i);
        p_apilar(P, X);
    }

    // Pregunto si esta llena
    if (p_es_llena(P)) {
        printf("Lista LLena \n");
    }
    else {
        printf("La Pila NO esta llena! \n");
    }

    p_mostrar(P);
    printf("\n");
    printf("Volvemos a mostrarla para verificar que no la perdidmos \n");
    p_mostrar(P);

    // Llamo a la pila de pares
    printf("\n");
    printf("Pila de Claves Pares: \n");
    Pila pp = RetornarClavesPares(P);
    p_mostrar(pp);

    // Vuelvo a mostrar la original
    printf("\n");
    printf("Pila Luego de procesar las Claves Pares: \n");
    p_mostrar(P);

    // verifico si esta ordenada
    if (EsPilaOrdenada(P)) {
        printf("LA PILA ESTA ORDENADA !!! \n");
    }
    else {
        printf("La pila esta DES-ORDENADA !!! \n");
    }
    p_mostrar(P);

    // Rompo el orden
    printf("----------------------------------------------------------------\n");
    printf("--- Borro el tope y le pongo un <-1> --- \n");
    printf("----------------------------------------------------------------\n");

    X = p_desapilar(P);
    X->clave = -1;
    p_apilar(P, X);
    p_mostrar(P);

    if (EsPilaOrdenada(P)) {
        printf("LA PILA ESTA ORDENADA !!! \n");
    }
    else {
        printf("La pila esta DES-ORDENADA !!! \n");
    }
    p_mostrar(P);

    return;
}

// retorno una nueva pila con claves pares
Pila RetornarClavesPares(Pila p){
    Pila pp;
    Pila paux;
    TipoElemento X = te_crear(0);
    pp = p_crear();
    paux = p_crear();

    // Recorro la pila desapilandola
    while (p_es_vacia(p) != true) {
        X = p_desapilar(p);
        if ((X->clave % 2) == 0) {
            p_apilar(pp, X);
        }
        p_apilar(paux, X);
    }

    // Reconstruyo la pila original
    while (p_es_vacia(paux) != true) {
        X = p_desapilar(paux);
        p_apilar(p, X);
    }

    // retorno la pila de pares
    return pp;
};

//--------------------------------------------------------
// Ejercicio del parcial
//--------------------------------------------------------
bool EsPilaOrdenada(Pila P){
    int ultclave = 0;
    TipoElemento X;
    Pila paux;
    bool esordenada = true;

    if (p_es_vacia(P)) {
        return true;
    }

    // compruebo si la pila esta ordenada
    paux = p_crear();
    X = p_desapilar(P);
    p_apilar(paux, X);
    ultclave = X->clave;

    while ((p_es_vacia(P) != true) && (esordenada == true)) {
        X = p_desapilar(P);
        if (X->clave > ultclave) {
            esordenada = false;
        }
        p_apilar(paux, X);
    }

    // retorno a la pila original
    while (p_es_vacia(paux) != true) {
        X = p_desapilar(paux);
        p_apilar(P, X);
    }

    return esordenada;
};
