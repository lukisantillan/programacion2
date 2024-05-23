#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
// FALTA COMPLEJIDADES
// a
// COMPLEJIDAD = 0(1) - Para listas con arreglos y 0(n) si se utiliza alguna de las otras dos implementaciones (Cursores, Punteros)
void es_hoja(NodoArbol n, Lista l)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hijoDer = n_hijoizquierdo(n);
    NodoArbol hijoIzq = n_hijoderecho(n);
    if (a_es_rama_nula(hijoIzq) && a_es_rama_nula(hijoDer))
    {
        l_agregar(l, te_crear_con_valor(n_recuperar(n)->clave, n));
    }
    es_hoja(hijoIzq, l);
    es_hoja(hijoDer, l);
}

Lista a_ej2_hojas(ArbolBinario A)
{
    Lista hojas = l_crear();
    es_hoja(a_raiz(A), hojas);
    return hojas;
}

// b
// COMPLEJIDAD = 0(1) - Para listas con arreglos y 0(n) si se utiliza alguna de las otras dos implementaciones (Cursores, Punteros)
void es_interno(NodoArbol n, Lista l, NodoArbol raiz)
{
    if (a_es_rama_nula(n))
    {
        return;
    }

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

Lista a_ej2_interiores(ArbolBinario A)
{
    Lista internos = l_crear();
    NodoArbol raiz = a_raiz(A);
    es_interno(raiz, internos, raiz);
    return internos;
}

// c
// COMPLEJIDAD = 0(1) - Para listas con arreglos y 0(n) si se utiliza alguna de las otras dos implementaciones (Cursores, Punteros)
void es_igual_a_clave(NodoArbol n, Lista l, int clave)
{
    if (a_es_rama_nula(n))
    {
        return;
    }

    NodoArbol hijoDer = n_hijoizquierdo(n);
    NodoArbol hijoIzq = n_hijoderecho(n);
    if (n_recuperar(n)->clave == clave)
    {
        l_agregar(l, te_crear_con_valor(n_recuperar(n)->clave, n));
    }
    es_igual_a_clave(hijoIzq, l, clave);
    es_igual_a_clave(hijoDer, l, clave);
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
    if (a_es_rama_nula(n))
    {
        return;
    }

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
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hijoIzq = n_hijoizquierdo(n);
    NodoArbol hijoDer = n_hijoderecho(n);
    if (n_recuperar(n)->clave == clavePadre)
    {
        if (!a_es_rama_nula(hijoDer))
        {
            l_agregar(l, te_crear_con_valor(n_recuperar(hijoDer)->clave, hijoDer));
        }
        if (!a_es_rama_nula(hijoIzq))
        {
            l_agregar(l, te_crear_con_valor(n_recuperar(hijoIzq)->clave, hijoIzq));
        }
        return;
    }
    encontrar_hijos(hijoIzq, clavePadre, l);
    encontrar_hijos(hijoDer, clavePadre, l);
}

Lista a_ej3_hijos(ArbolBinario A, int clavepadre)
{
    Lista hijos = l_crear();
    encontrar_hijos(a_raiz(A), clavepadre, hijos);
    return hijos;
}

// c
void encontrar_hermano(NodoArbol n, int clave, int *claveHermano)
{
    if (a_es_rama_nula(n))
    {
        return;
    }

    NodoArbol hijoDer = n_hijoizquierdo(n);
    NodoArbol hijoIzq = n_hijoderecho(n);
    if (hijoDer != NULL && hijoIzq != NULL)
    {
        if (n_recuperar(hijoDer)->clave == clave)
        {
            *claveHermano = n_recuperar(hijoIzq)->clave;
            return;
        }
        else if (n_recuperar(hijoIzq)->clave == clave)
        {
            *claveHermano = n_recuperar(hijoDer)->clave;
            return;
        }
    }
    encontrar_hermano(hijoIzq, clave, claveHermano);
    encontrar_hermano(hijoDer, clave, claveHermano);
}

int a_ej3_hermano(ArbolBinario A, int clave)
{
    int *claveHermano = malloc(sizeof(int));
    *claveHermano = -999;
    NodoArbol raiz = a_raiz(A);
    encontrar_hermano(raiz, clave, claveHermano);
    int resultado = *claveHermano;
    free(claveHermano);
    return resultado;
}

// d
int calcularNivelNodo(NodoArbol n, int clave, int nivel)
{
    if (a_es_rama_nula(n))
    {
        return -1;
    }
    if (n_recuperar(n)->clave == clave)
    {
        return nivel;
    }
    int nivel_izquierdo = calcularNivelNodo(n_hijoizquierdo(n), clave, nivel + 1);
    if (nivel_izquierdo != -1)
    {
        return nivel_izquierdo;
    }
    return calcularNivelNodo(n_hijoderecho(n), clave, nivel + 1);
}

int a_ej3_nivel(ArbolBinario A, int clave)
{
    int nivel = calcularNivelNodo(a_raiz(A), clave, 0);
    return nivel;
}

// e
int altura_arbol(NodoArbol n)
{
    if (n == NULL)
    {
        return -1; // no se encontro la clave
    }

    int ai = altura_arbol(n->hi);
    int ad = altura_arbol(n->hd);
    if (ai > ad)
    {
        return ai + 1;
    }
    else
    {
        return ad + 1;
    }
}

void busquedadelnodo(NodoArbol n, int clave, NodoArbol *nodo_encontrado)
{
    if (n != NULL)
    {
        if (n_recuperar(n)->clave == clave)
        {
            *nodo_encontrado = n;
            return;
        }
        busquedadelnodo(n->hi, clave, nodo_encontrado);
        busquedadelnodo(n->hd, clave, nodo_encontrado);
    }
}

int a_ej3_alturarama(ArbolBinario A, int clave)
{
    NodoArbol raiz = a_raiz(A);
    NodoArbol nodoencontrado = NULL;
    int alt = 0;
    if (a_es_vacio(A))
    {
        return alt;
    }
    else
    {
        busquedadelnodo(raiz, clave, &nodoencontrado);
        if (nodoencontrado != NULL)
        {
            int altura = altura_arbol(nodoencontrado);
            return altura;
        }
        else
        {
            return -1;
        }
    }
}

// f
void nivel_nodos(NodoArbol n, int nivel, int niv_aux, Lista *list)
{

    if (n == NULL)
    {
        return;
    }
    if (nivel == niv_aux)
    {
        TipoElemento ele = n_recuperar(n);
        l_agregar(*list, ele);
    }

    nivel_nodos(n->hi, nivel, niv_aux + 1, list);
    nivel_nodos(n->hd, nivel, niv_aux + 1, list);
}
Lista a_ej3_clavesmismonivel(ArbolBinario A, int nivel)
{
    NodoArbol raiz = a_raiz(A);
    int niv = 0;
    Lista lista_nodos = l_crear();
    nivel_nodos(raiz, nivel, niv, &lista_nodos);
    return lista_nodos;
}

// Punto 4

// a
void recorrerPorAnchura(NodoArbol n, Lista l, Cola c)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hijoIzq = n_hijoizquierdo(n);
    NodoArbol hijoDer = n_hijoderecho(n);
    if (!a_es_rama_nula(hijoDer))
    {
        l_agregar(l, te_crear_con_valor(n_recuperar(n)->clave, n));
        if (!a_es_rama_nula(hijoIzq))
        {
            TipoElemento eleAencolar = te_crear_con_valor(n_recuperar(hijoIzq)->clave, hijoIzq);
            c_encolar(c, eleAencolar);
        }
        recorrerPorAnchura(hijoDer, l, c);
    }
    else
    {
        l_agregar(l, te_crear_con_valor(n_recuperar(n)->clave, n));
        if (!a_es_rama_nula(hijoIzq))
        {
            TipoElemento eleAencolar = te_crear_con_valor(n_recuperar(hijoIzq)->clave, hijoIzq);
            c_encolar(c, eleAencolar);
        }
        if (!c_es_vacia(c))
        {
            TipoElemento eleAdesencolar = c_desencolar(c);
            recorrerPorAnchura(eleAdesencolar->valor, l, c);
        }
    }
}

Lista a_ej4_anchura(ArbolBinario A)
{
    Lista resultado = l_crear();
    Cola ColaAux = c_crear();
    recorrerPorAnchura(a_raiz(A), resultado, ColaAux);
    return resultado;
}

// b
void acumuladorHojas(NodoArbol n, int *acumulador)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hijoIzq = n_hijoizquierdo(n);
    NodoArbol hijoDer = n_hijoderecho(n);
    if (a_es_rama_nula(hijoIzq))
    {
        (*acumulador)++;
    }
    acumuladorHojas(hijoIzq, acumulador);
    acumuladorHojas(hijoDer, acumulador);
}

int a_ej4_q_hojas(ArbolBinario A)
{
    int *acumulador = malloc(sizeof(int));
    *acumulador = 0;
    acumuladorHojas(a_raiz(A), acumulador);
    return *acumulador;
}

// c
void similarAux(NodoArbol a, NodoArbol b, bool *flag)
{
    if (!a_es_rama_nula(a) || !a_es_rama_nula(b))
    {
        NodoArbol hijoDer1 = n_hijoderecho(a);
        NodoArbol hijoIzq1 = n_hijoizquierdo(a);
        NodoArbol hijoDer2 = n_hijoderecho(b);
        NodoArbol hijoIzq2 = n_hijoizquierdo(b);
        if (a_es_rama_nula(hijoIzq1) && a_es_rama_nula(hijoIzq2))
        {
            similarAux(hijoIzq1, hijoIzq2, flag);
        }
        else if (a_es_rama_nula(hijoDer1) && a_es_rama_nula(hijoDer2))
        {
            similarAux(hijoIzq1, hijoIzq2, flag);
        }
        else
        {
            *flag = false;
            return;
        }
    }
}

bool a_ej4_similares(ArbolBinario A, ArbolBinario B)
{
    bool *flag = malloc(sizeof(bool));
    *flag = true;
    similarAux(a_raiz(A), a_raiz(B), flag);
    bool resultado = *flag;
    free(flag);
    return resultado;
}

// Punto 7
void equivalenteAux(NodoArbol a, NodoArbol b, bool *flag)
{
    if (!a_es_rama_nula(a) || !a_es_rama_nula(b))
    {
        NodoArbol hijoDer1 = n_hijoderecho(a);
        NodoArbol hijoIzq1 = n_hijoizquierdo(a);
        NodoArbol hijoDer2 = n_hijoderecho(b);
        NodoArbol hijoIzq2 = n_hijoizquierdo(b);
        if (!a_es_rama_nula(hijoDer1) && !a_es_rama_nula(hijoDer2))
        {
            if (n_recuperar(hijoDer1)->clave != n_recuperar(hijoDer2)->clave)
            {
                *flag = false;
                return;
            }
            equivalenteAux(hijoDer1, hijoDer2, flag);
        }
        else if (!a_es_rama_nula(hijoIzq1) && !a_es_rama_nula(hijoIzq2))
        {
            if (n_recuperar(hijoIzq1)->clave != n_recuperar(hijoIzq2)->clave)
            {
                *flag = false;
                return;
            }
            equivalenteAux(hijoIzq1, hijoIzq2, flag);
        }
        else if (a_es_rama_nula(hijoIzq1) && a_es_rama_nula(hijoIzq2))
        {
            equivalenteAux(hijoIzq1, hijoIzq2, flag);
        }
        else if (a_es_rama_nula(hijoDer1) && a_es_rama_nula(hijoDer2))
        {
            equivalenteAux(hijoIzq1, hijoIzq2, flag);
        }
        else
        {
            *flag = false;
            return;
        }
    }
}

bool a_ej7_equivalente(ArbolBinario A, ArbolBinario B)
{
    bool *flag = malloc(sizeof(bool));
    *flag = true;
    equivalenteAux(a_raiz(A), a_raiz(B), flag);
    bool resultado = *flag;
    free(flag);
    return resultado;
}

// Punto 8
// a
void alturaAux(NodoArbol n, int *alturaActual, int *acumulador)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hijoDer = n_hijoderecho(n);
    NodoArbol hijoIzq = n_hijoizquierdo(n);
    if (!a_es_rama_nula(hijoIzq))
    {
        *acumulador += 1;
    }
    else
    {
        if (*acumulador > *alturaActual)
        {
            *alturaActual = *acumulador;
            *acumulador = 0;
        }
        else
            *acumulador = 0;
    }
    alturaAux(hijoIzq, alturaActual, acumulador);
    alturaAux(hijoDer, alturaActual, acumulador);
}

int c_ej8_altura(ArbolBinario A)
{
    int *alturaActual = malloc(sizeof(int));
    int *acumulador = malloc(sizeof(int));
    *alturaActual = 0;
    *acumulador = 0;
    alturaAux(a_raiz(A), alturaActual, acumulador);
    return *alturaActual;
}

// c
void internosAux(NodoArbol n, Lista nodosInternos, NodoArbol raiz)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hijoDer = n_hijoderecho(n);
    NodoArbol hijoIzq = n_hijoizquierdo(n);
    if (n != raiz)
    {
        if (!a_es_rama_nula(hijoIzq))
        {
            l_agregar(nodosInternos, te_crear_con_valor(n_recuperar(n)->clave, n));
        }
    }

    internosAux(hijoIzq, nodosInternos, raiz);
    internosAux(hijoDer, nodosInternos, raiz);
}

Lista c_ej8_internos(ArbolBinario A)
{
    Lista nodosInternos = l_crear();
    NodoArbol raiz = a_raiz(A);
    internosAux(raiz, nodosInternos, raiz);
    return nodosInternos;
}

// 9
// FALTA RECURSIVIDAD
void auxRellenarArbolAvl(NodoArbol n, ArbolAVL resu)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hd = n_hijoderecho(n);
    NodoArbol hi = n_hijoizquierdo(n);
    avl_insertar(resu, te_crear_con_valor(n_recuperar(n)->clave, n));
    auxRellenarArbolAvl(hi, resu);
    auxRellenarArbolAvl(hd, resu);
}

ArbolAVL a_ej9_construiravl(ArbolBinario A)
{
    ArbolAVL resultado = avl_crear();
    auxRellenarArbolAvl(a_raiz(A), resultado);
    return resultado;
}

int a_ej9_diferenciaalturas(ArbolBinario A, ArbolAVL AVL)
{
    int alturaArbolBinario = altura_arbol(a_raiz(A));
    int alturaAVL = altura_arbol(avl_raiz(AVL));
    return alturaArbolBinario - alturaAVL;
}

// Ejercicio 10

Lista a_ej10_generarlistaclaves(int cantidadclavesagenerar, int valorminimo, int valormaximo)
{
    Lista lista = l_crear();
    for (int i = 0; i < cantidadclavesagenerar; i++)
    {
        int clave = rand() % (valormaximo - valorminimo + 1) + valorminimo;

        while (l_buscar(lista, clave))
        {
            clave = rand() % (valormaximo - valorminimo + 1) + valorminimo;
        }

        l_agregar(lista, te_crear(clave));
    }
    return lista;
}

ArbolBinarioBusqueda a_ej10_crearABB(Lista L)
{
    ArbolBinarioBusqueda resultado = abb_crear();
    Iterador ite = iterador(L);
    while (hay_siguiente(ite))
    {
        TipoElemento ele = siguiente(ite);
        abb_insertar(resultado, ele);
    }
    return resultado;
}

ArbolAVL a_ej10_crearAVL(Lista L)
{
    ArbolAVL resultado = avl_crear();
    Iterador ite = iterador(L);
    while (hay_siguiente(ite))
    {
        TipoElemento ele = siguiente(ite);
        avl_insertar(resultado, ele);
    }
    return resultado;
}

int a_ej10_difalturas(ArbolBinarioBusqueda ABB, ArbolAVL AVL)
{
    int resultadoABB = altura_arbol(abb_raiz(ABB));
    int resultadoAVL = altura_arbol(avl_raiz(AVL));
    return resultadoABB - resultadoAVL;
}

Lista a_ej10_comparacionarboles(int N_repeticiones, int valorminimo, int valormaximo, int cantidaclavesagenerar)
{
    Lista resultado = l_crear();
    int i = 0;
    while (i < N_repeticiones)
    {
        Lista clavesGeneradas = a_ej10_generarlistaclaves(cantidaclavesagenerar, valorminimo, valormaximo);
        ArbolAVL avl = a_ej10_crearAVL(clavesGeneradas);
        ArbolBinarioBusqueda abb = a_ej10_crearABB(clavesGeneradas);
        int diferenciaAltura = a_ej10_difalturas(abb, avl);
        l_agregar(resultado, te_crear(diferenciaAltura));
        i++;
    }
    return resultado;
}

int main()
{
    srand(time(NULL));
    ArbolBinario arbol = a_crear();
    arbol = cargarArbol();
    printf("----------------------\n");
    /*
    ArbolBinario arbol2 = a_crear();
    arbol2 = cargarArbol();
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
    // int clavePadre = 10;
    // Lista resu = a_ej3_hijos(arbol, clavePadre);
    // if (l_es_vacia(resu))
    // {
    //     printf("La clave era una hoja, por lo tanto no tenia hijos\n");
    // }
    // else
    // {
    //     printf("El padre %d, tiene el(los) siguiente(s) hijo(s)..\n", clavePadre);
    //     l_mostrar(resu);
    // }
    // int clave = 2;
    // int resultado = a_ej3_hermano(arbol, clave);
    // if (resultado == -999)
    // {
    //     printf("Hay 2 posibles opciones..\n");
    //     printf("1 - El hijo con la clave %d, no tiene hermano\n", clave);
    //     printf("2 - No existe un hijo con la clave %d, por lo tanto no existe un hermano\n", clave);
    // }
    // else
    // {
    //     printf("El hijo %d, tiene como hermano a %d \n", clave, resultado);
    // }

    // int clave = 5;
    // int resultado = a_ej3_nivel(arbol, clave);
    // if (resultado == -1)
    // {
    //     printf("El nodo con la clave %d, no se encuentra en el arbol..\n", clave);
    // }
    // else if (resultado == 0)
    // {
    //     printf("El nodo con la clave %d, se encuentra en la raiz..\n", clave);
    // }
    // else
    //     printf("El nodo con la clave %d se encuentra en el nivel numero : %d..\n", clave, resultado);

    // int clave = 150;
    // int altura = a_ej3_alturarama(arbol, clave);
    // if (altura == -1)
    // {
    //     printf("No se encontro la clave en el arbol\n");
    // }
    // else if (altura == 0)
    // {
    //     printf("el arbol esta vacio o es una hoja(altura 0) \n");
    // }
    // else
    // {
    //     printf("El nodo con la clave %d tiene una altura de: %d \n", clave, altura);
    // }
    // int nivel = 2;
    // Lista lis = a_ej3_clavesmismonivel(arbol, nivel);
    // printf("En el nivel: %d, se encuentran los siguientes Nodos: \n", nivel);
    // l_mostrar(lis);
    // int resultado = a_ej4_q_hojas(arbol);
    // printf("La cantidad de hojas es %d\n", resultado);

    // Lista resu = a_ej4_anchura(arbol);
    // l_mostrar(resu);
    // bool resultado = a_ej4_similares(arbol, arbol2);
    // if (resultado)
    // {
    //     printf("Los arboles son similares\n");
    // }
    // else
    //     printf("Los arboles no son similares\n");

    // bool resultado = a_ej7_equivalente(arbol, arbol2);
    // if (resultado)
    // {
    //     printf("Los arboles son equvalentes\n");
    // }
    // else
    //     printf("Los arboles no son equivalentes\n");
    // Lista resultadoEje8c = c_ej8_internos(arbol);
    // printf("Los nodos internos son: \n");
    // if (!l_es_vacia(resultadoEje8c))
    // {
    //     l_mostrar(resultadoEje8c);
    // }
    // else
    //     printf("No hay nodos internos\n");

    // int resultado8a = c_ej8_altura(arbol);
    // printf("La altura del arbol n-ario es %i\n", resultado8a);
    // ArbolAVL arbolAvl = a_ej9_construiravl(arbol);
    // int resultadoDiferenciaAltura = a_ej9_diferenciaalturas(arbol, arbolAvl);
    // printf("La diferencia entre alturas considerando (ARBOL - ARBOL AVL) es..  %i\n", resultadoDiferenciaAltura);

     Lista lista = a_ej10_comparacionarboles(8,10,20,10);
     l_mostrar(lista);
    return 0;
}

// gcc -o output ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c ../libs/nodos/nodo.c ../libs/arboles/arbol-binario.c ../libs/colas/colas_arreglos.c ../libs/arboles/arbol-avl.c main.c