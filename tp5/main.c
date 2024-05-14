#include <stdio.h>
#include <stdlib.h>

#include "./TP_5_Arboles.h"

// FUNCIONES EXTRAS
int solicitarNumero(bool *variable)
{
    printf("\n| ¿Desea agregar un numero? (s/n): ");
    while (1)
    {
        char opcion;
        scanf(" %c", &opcion);
        if (opcion == 's')
        {
            int numero;
            printf("\nIngrese el numero: ");
            while (scanf("%d", &numero) != 1)
            {
                printf("\nError: Ingresa un número válido para la cantidad de elementos: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }
            return numero;
        }
        else if (opcion == 'n')
        {
            *variable = false;
            return -1;
        }
        else
        {
            printf("| Opcion no valida, intente nuevamente: ");
        }
    }
}

void cargarPreOrden(ArbolBinario a, NodoArbol nodo, int orden)
{
    bool b = true;
    int n = solicitarNumero(&b);
    NodoArbol pa;
    if (b)
    {
        if (orden == 0)
        {
            pa = a_establecer_raiz(a, te_crear(n));
        }
        else if (orden == -1)
        {
            pa = a_conectar_hi(a, nodo, te_crear(n));
        }
        else
            pa = a_conectar_hd(a, nodo, te_crear(n));
        // PREORDEN
        cargarPreOrden(a, pa, -1);
        printf("Hijo derecho\n");
        cargarPreOrden(a, pa, 1);
    }
}

ArbolBinario cargarArbol()
{
    ArbolBinario arbol = a_crear();
    cargarPreOrden(arbol, NULL, 0);
    return arbol;
}

// Punto 2

// a
void es_hoja(NodoArbol n, Lista l)
{
    if (!a_es_rama_nula(n))
    {
        NodoArbol hijoDer = n_hijoizquierdo(n);
        NodoArbol hijoIzq = n_hijoderecho(n);
        if (a_es_rama_nula(hijoIzq) && a_es_rama_nula(hijoDer))
        {
            TipoElemento ele = te_crear(n_recuperar(n)->clave);
            l_agregar(l, ele);
        }
        es_hoja(hijoIzq, l);
        es_hoja(hijoDer, l);
    }
}

Lista a_ej2_hojas(ArbolBinario A)
{
    Lista hojas = l_crear();
    es_hoja(a_raiz(A), hojas);
    return hojas;
}

// b

void es_interno(NodoArbol n, Lista l, NodoArbol raiz)
{
    if (!a_es_rama_nula(n))
    {
        NodoArbol hijoDer = n_hijoizquierdo(n);
        NodoArbol hijoIzq = n_hijoderecho(n);
        if (n != raiz)
        {
            if (!a_es_rama_nula(hijoIzq) || !a_es_rama_nula(hijoDer))
            {
                l_agregar(l, te_crear_con_valor(n_recuperar(n)->clave, n));
            }
        
        }
        es_interno(hijoIzq, l, raiz);
        es_interno(hijoDer, l, raiz);
    }
}

Lista a_ej2_interiores(ArbolBinario A)
{
    Lista internos = l_crear();
    NodoArbol raiz = a_raiz(A);
    printf("| Clave: %d, Posicion: %p\n", raiz->datos->clave, (void *)raiz->datos->valor);
    es_interno(raiz, internos, raiz);
    return internos;
}

// c
void es_igual_a_clave(NodoArbol n, Lista l, int clave)
{
    if (!a_es_rama_nula(n))
    {
        NodoArbol hijoDer = n_hijoizquierdo(n);
        NodoArbol hijoIzq = n_hijoderecho(n);
        if (n_recuperar(n)->clave == clave)
        {
            l_agregar(l, te_crear_con_valor(n_recuperar(n)->clave, n));
        }
        es_igual_a_clave(hijoIzq, l, clave);
        es_igual_a_clave(hijoDer, l, clave);
    }
}

Lista a_ej2_buscarclave(ArbolBinario A, int clave)
{
    Lista direcciones = l_crear();
    es_igual_a_clave(a_raiz(A), direcciones, clave);
    return direcciones;
}

int main()
{
    ArbolBinario arbol = a_crear();
    arbol = cargarArbol();
    Lista hojas = a_ej2_hojas(arbol);
    l_mostrar(hojas);
    printf("\n ----------------------------");
    Lista interiores = a_ej2_interiores(arbol);
    l_mostrar(interiores);
    printf("\n ----------------------------");
    Lista igual = a_ej2_buscarclave(arbol, 10);
    Iterador iteIg = iterador(igual);
    while (hay_siguiente(iteIg))
    {
        TipoElemento ele = siguiente(iteIg);
        printf("\n| Clave: %d, Posicion: %p", ele->clave, (void *)ele->valor);
    }

    return 0;
}
