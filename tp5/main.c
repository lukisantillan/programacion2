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
            l_agregar(l, te_crear_con_valor(n_recuperar(n)->clave, n));
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

// Punto 3
// a
void encontrar_padre(NodoArbol n, int clavehijo, int *clavePadre)
{
    if (!a_es_rama_nula(n))
    {
        NodoArbol hijoDer = n_hijoizquierdo(n);
        NodoArbol hijoIzq = n_hijoderecho(n);
        if ((hijoDer != NULL && n_recuperar(hijoDer)->clave == clavehijo) ||
            (hijoIzq != NULL && n_recuperar(hijoIzq)->clave == clavehijo))
        {
            *clavePadre = n_recuperar(n)->clave;
            return;
        }
        encontrar_padre(hijoIzq, clavehijo, clavePadre);
        encontrar_padre(hijoDer, clavehijo, clavePadre);
    }
}

int a_ej3_clavepadre(ArbolBinario A, int clavehijo)
{
    int *clavePadre = malloc(sizeof(int));
    *clavePadre = -999;
    NodoArbol raiz = a_raiz(A);
    if (n_recuperar(raiz)->clave == clavehijo)
    {
        return 999;
    }

    encontrar_padre(raiz, clavehijo, clavePadre);
    int resultado = *clavePadre;
    free(clavePadre);
    return resultado;
}

// b
void encontrar_hijos(NodoArbol n, int clavePadre, Lista l)
{
    if (!a_es_rama_nula(n))
    {
        NodoArbol hijoIzq = n_hijoizquierdo(n);
        NodoArbol hijoDer = n_hijoderecho(n);
        if (n_recuperar(n)->clave == clavePadre)
        {
            l_agregar(l, te_crear_con_valor(n_recuperar(hijoIzq)->clave, n));
            l_agregar(l, te_crear_con_valor(n_recuperar(hijoDer)->clave, n));
            return ;
        }
        encontrar_hijos(hijoIzq, clavePadre, l);
        encontrar_hijos(hijoDer, clavePadre, l);
    }
}

Lista a_ej3_hijos(ArbolBinario A, int clavepadre)
{
    Lista hijos = l_crear();
    encontrar_hijos(a_raiz(A), clavepadre, hijos);
    return hijos;
}

int main()
{
    ArbolBinario arbol = a_crear();
    arbol = cargarArbol();
    /*
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

    int hijo = 2;
    int resultado = a_ej3_clavepadre(arbol, hijo);
    if (resultado == -999)
    {
        printf("El hijo no existe en el arbol, por lo tanto no se pudo buscar el padre\n");
    }
    else if (resultado == 999)
    {
        printf("La clave enviada es la raiz del arbol, por lo no tiene padre\n");
    }
    else
    {
        printf("El hijo %d, tiene como padre a %d \n", hijo, resultado);
    }
    */
   int clavePadre = 10;
   Lista resu = a_ej3_hijos(arbol,clavePadre);
   if (l_es_vacia(resu))
   {
    printf("La clave era una hoja, por lo tanto no tenia hijos\n");
   } else 
   {
    printf("El padre %d, tiene el(los) siguiente(s) hijo(s)..\n", clavePadre);
    l_mostrar(resu);
   }
   

    return 0;
}
