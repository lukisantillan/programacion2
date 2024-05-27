#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#include "./TP_5_Arboles.h"

// FUNCIONES EXTRAS

void clearScreen()
{
    system("clear");
}

void waitForKey()
{
    printf("\nPresione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();

    system("clear");
}

char transformarClave(int clave, char tipo)
{
    if (tipo == 'n')
    {
        return (int)clave;
    }
    else
    {
        return (char)clave;
    }
}

void buscarClaveAux(NodoArbol n, bool *flag, int clave)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hi = n_hijoizquierdo(n);
    NodoArbol hd = n_hijoderecho(n);
    if (n_recuperar(n)->clave == clave)
    {
        *flag = true;
        return;
    }
    buscarClaveAux(hi, flag, clave);
    buscarClaveAux(hd, flag, clave);
}
bool buscarClave(NodoArbol n, int clave)
{
    bool flag = false;
    buscarClaveAux(n, &flag, clave);
    return flag;
}

int solicitarNumero(bool *variable)
{
    printf("\n| Desea agregar un numero? (s/n): ");
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

char solicitarLetra(bool *variable)
{
    printf("\n| Desea agregar una letra? (s/n): ");
    while (1)
    {
        char opcion;
        scanf(" %c", &opcion);
        opcion = tolower(opcion); // Convertir a minúscula para simplificar la comparación
        if (opcion == 's')
        {
            char letra;
            printf("\nIngrese una letra (A-Z): ");
            while (1)
            {
                scanf(" %c", &letra);
                letra = toupper(letra); // Convertir a mayúscula para validar fácilmente
                if (letra >= 'A' && letra <= 'Z')
                {
                    return letra;
                }
                else
                {
                    printf("\nError: Ingresa una letra válida (A-Z): ");
                    while (getchar() != '\n')
                    {
                        // clear input buffer
                    }
                }
            }
        }
        else if (opcion == 'n')
        {
            *variable = false;
            return '\0'; // Retornar un carácter nulo para indicar que no se ingresó una letra
        }
        else
        {
            printf("| Opción no válida, intente nuevamente: ");
        }
    }
}

void mostrarArbolRec(NodoArbol raiz, char prefijo[], int esIzquierda, char tipo)
{
    if (raiz == NULL)
    {
        return;
    }

    printf("%s", prefijo);

    if (esIzquierda)
    {
        printf("|-- ");
    }
    else
    {
        printf("|__ ");
    }

    TipoElemento ele = n_recuperar(raiz);
    if (tipo == 'n')
    {
        printf("%d\n", ele->clave);
    }
    else if (tipo == 'l')
    {
        printf("%c\n", (char)ele->clave);
    }

    char nuevoPrefijo[1000];
    snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "%s%s", prefijo, esIzquierda ? "|   " : "    ");

    mostrarArbolRec(n_hijoizquierdo(raiz), nuevoPrefijo, 1, tipo);
    mostrarArbolRec(n_hijoderecho(raiz), nuevoPrefijo, 0, tipo);
}

// Función para mostrar el árbol
void mostrarArbol(NodoArbol raiz, char tipo)
{
    if (raiz == NULL)
    {
        return;
    }

    if (tipo == 'n')
    {
        printf("%d\n", n_recuperar(raiz)->clave);
    }
    else if (tipo == 'l')
    {
        printf("%c\n", (char)n_recuperar(raiz)->clave);
    }

    mostrarArbolRec(n_hijoizquierdo(raiz), "", 1, tipo); // Llama a los hijos con prefijos adecuados
    mostrarArbolRec(n_hijoderecho(raiz), "", 0, tipo);
}

void cargarPreOrden(ArbolBinario arbol, NodoArbol nodo, int orden, char tipo)
{
    bool b = true;
    if (tipo == 'n')
    {
        int n = solicitarNumero(&b);
        if (b)
        {
            if (buscarClave(a_raiz(arbol), n))
            {
                printf("El número ya existe en el árbol, ingrese otro número\n");
                cargarPreOrden(arbol, nodo, orden, tipo);
            }
            else
            {
                NodoArbol pa;
                if (orden == 0)
                {
                    pa = a_establecer_raiz(arbol, te_crear(n));
                }
                else if (orden == -1)
                {
                    pa = a_conectar_hi(arbol, nodo, te_crear(n));
                }
                else
                {
                    pa = a_conectar_hd(arbol, nodo, te_crear(n));
                }
                printf("El arbol esta quedando de la siguiente manera : \n\n");
                mostrarArbol(a_raiz(arbol), tipo);
                cargarPreOrden(arbol, pa, -1, tipo);
                printf("Hijo derecho\n");
                cargarPreOrden(arbol, pa, 1, tipo);
            }
        }
    }
    else
    {
        char l = solicitarLetra(&b);

        if (b)
        {
            if (buscarClave(a_raiz(arbol), (int)l))
            {
                printf("La letra ya existe en el árbol, ingrese otra letra\n");
                cargarPreOrden(arbol, nodo, orden, tipo);
            }
            else
            {
                NodoArbol pa;
                if (orden == 0)
                {
                    pa = a_establecer_raiz(arbol, te_crear(l));
                }
                else if (orden == -1)
                {
                    pa = a_conectar_hi(arbol, nodo, te_crear(l));
                }
                else
                {
                    pa = a_conectar_hd(arbol, nodo, te_crear(l));
                }
                printf("El arbol esta quedando de la siguiente manera : \n\n");
                mostrarArbol(a_raiz(arbol), tipo);
                cargarPreOrden(arbol, pa, -1, tipo);
                printf("Hijo derecho\n");
                cargarPreOrden(arbol, pa, 1, tipo);
            }
        }
    }
}

ArbolBinario cargarArbol(char *tipo)
{
    ArbolBinario arbol = a_crear();
    printf("Ingrese el tipo de elementos a cargar (1: numeros, 2: letras): ");
    while (1)
    {
        char opcion;
        scanf(" %c", &opcion);
        if (opcion == '1')
        {
            *tipo = 'n';
            break;
        }
        else if (opcion == '2')
        {
            *tipo = 'l';
            break;
        }
        else
        {
            printf("Opción no válida, intente nuevamente: ");
        }
    }
    cargarPreOrden(arbol, NULL, 0, *tipo); // Pasando el valor de tipo, no la dirección
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
    NodoArbol hijoizq = n_hijoizquierdo(n);
    NodoArbol hijoder = n_hijoderecho(n);
    if (!a_es_rama_nula(n))
    {
        if (n_recuperar(n)->clave == clave)
        {
            *nodo_encontrado = n;
            return;
        }
        busquedadelnodo(hijoizq, clave, nodo_encontrado);
        busquedadelnodo(hijoder, clave, nodo_encontrado);
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
    NodoArbol hijoizq = n_hijoizquierdo(n);
    NodoArbol hijoder = n_hijoderecho(n);
    if (a_es_rama_nula(n))
    {

        return;
    }
    if (nivel == niv_aux)
    {
        TipoElemento ele = n_recuperar(n);
        l_agregar(*list, ele);
    }

    nivel_nodos(hijoizq, nivel, niv_aux + 1, list);
    nivel_nodos(hijoder, nivel, niv_aux + 1, list);
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
// d
void padreAux(NodoArbol n, TipoElemento *posiblePa, Cola c, int clave)
{
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hd = n_hijoderecho(n);
    NodoArbol hi = n_hijoizquierdo(n);
    if (a_es_rama_nula(hd) && !a_es_rama_nula(hi))
    {
        *posiblePa = te_crear_con_valor(n_recuperar(n)->clave, n);
        if (n_recuperar(hi)->clave == clave)
        {
            return;
        }
        padreAux(hi, posiblePa, c, clave);
    }
    else if (!a_es_rama_nula(hd) && !a_es_rama_nula(hi))
    {
        TipoElemento eleAencolar = te_crear_con_valor(n_recuperar(n)->clave, n);
        c_encolar(c, eleAencolar);
        if (n_recuperar(hd)->clave == clave)
        {
            return;
        }
        padreAux(hd, posiblePa, c, clave);
    }
    else if (a_es_rama_nula(hi) && !a_es_rama_nula(hd))
    {
        if (n_recuperar(hd)->clave == clave)
        {
            return;
        }
        padreAux(hd, posiblePa, c, clave);
    }
    else if (a_es_rama_nula(hd) && a_es_rama_nula(hi))
    {
        if (n_recuperar(n)->clave == clave)
        {
            return;
        }
        c_mostrar(c);
        TipoElemento eleAdesencolar = c_desencolar(c);
        *posiblePa = te_crear_con_valor(eleAdesencolar->clave, eleAdesencolar->valor);
        NodoArbol hi = n_hijoizquierdo(eleAdesencolar->valor);
        padreAux(hi, posiblePa, c, clave);
    }
}

TipoElemento a_ej4_padre(ArbolBinario A, int clave)
{
    NodoArbol raiz = a_raiz(A);
    bool hijoIzq = a_es_rama_nula(n_hijoizquierdo(raiz));
    TipoElemento resultado = malloc(sizeof(TipoElemento));
    if (hijoIzq)
    {
        free(resultado);
        printf("El arbol n-ario esta mal formado, no se puede buscar el padre de un nodo que no tiene hijos\n");
        return resultado;
    }
    Cola aux = c_crear();
    padreAux(raiz, &resultado, aux, clave);
    return resultado;
}
// e
void lista_hermanos(NodoArbol n, Lista *lis, int clave, NodoArbol *padre, NodoArbol *padreant)
{
    if (!a_es_rama_nula(n))
    {
        NodoArbol hijoDer1 = n_hijoderecho(n);
        NodoArbol hijoIzq1 = n_hijoizquierdo(n);
        if (n_recuperar(n)->clave == clave || !a_es_rama_nula(*padre))
        {
            *padre = n;
            if (!a_es_rama_nula(hijoDer1))
            {
                TipoElemento ele = n_recuperar(hijoDer1);
                l_agregar(*lis, ele);
                padreant = padre;
                lista_hermanos(hijoDer1, lis, clave, padre, padreant);
            }
            // sino la lista estara vacia
            return;
        }
        lista_hermanos(hijoIzq1, lis, clave, padre, padreant);
        lista_hermanos(hijoDer1, lis, clave, padre, padreant);
    }
}
Lista a_ej4_hermanos(ArbolBinario A, int clave)
{
    Lista l = l_crear();
    NodoArbol n = a_raiz(A);
    NodoArbol padre = NULL;
    NodoArbol padreant = NULL;
    lista_hermanos(n, &l, clave, &padre, &padreant);
    return l;
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
// b
void auxNivel(NodoArbol n, int clave, int *nivel, int c)
{
    TipoElemento X;
    if (!a_es_rama_nula(n))
    {
        X = n_recuperar(n);
        if (X->clave == clave)
        {
            *nivel = c;
            return;
        }
        else
        {
            auxNivel(n_hijoizquierdo(n), clave, nivel, c + 1);
            auxNivel(n_hijoderecho(n), clave, nivel, c);
        }
    }
}

int c_ej8_nivel(ArbolBinario A, int clave)
{
    int nivel = -1;
    auxNivel(a_raiz(A), clave, &nivel, 0);
    return nivel;
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

// d
void sacarHojasAux(NodoArbol n, Lista *l)
{
    TipoElemento ele;
    if (a_es_rama_nula(n))
    {
        return;
    }
    NodoArbol hd = n_hijoderecho(n);
    NodoArbol hi = n_hijoizquierdo(n);
    if (a_es_rama_nula(hi))
    {
        ele = te_crear(n_recuperar(n)->clave);
        l_agregar(*l, ele);
    }
    sacarHojasAux(hi, l);
    sacarHojasAux(hd, l);
}

bool c_ej8_hojasmismonivel(ArbolBinario A)
{
    Lista listaHojas = l_crear();
    sacarHojasAux(a_raiz(A), &listaHojas);
    l_mostrar(listaHojas);
    Iterador ite = iterador(listaHojas);
    bool resultado = true;
    bool flagPrimero = false;
    int nivelAct;
    int nivelSacado;
    while (hay_siguiente(ite) && resultado)
    {
        TipoElemento ele1 = siguiente(ite);
        int clave = ele1->clave;
        printf("Clave = %d \n", clave);
        if (!flagPrimero)
        {
            nivelAct = c_ej8_nivel(A, clave);
            nivelSacado = nivelAct;
            flagPrimero = true;
        }
        else
        {
            nivelSacado = c_ej8_nivel(A, clave);
            if (nivelSacado != nivelAct)
            {
                resultado = false;
            }
        }
    }
    return resultado;
}

// 9
// COMPLEJIDAD 0(1)
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

        while (l_buscar(lista, clave) != NULL)
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

// EN EL MAIN VALIDAR QUE N_REPETICIONES SEA > 0, QUE CANTIDADDECLAVES > 0, VALIDAR QUE EL VALOR ABS DE MINIMO - MAXIMO > 10*CANTIDADCLAVES A GENERAR.
Lista a_ej10_comparacionarboles(int N_repeticiones, int valorminimo, int valormaximo, int cantidaclavesagenerar)
{
    Lista resultado = l_crear();
    int i = 0;
    while (i < N_repeticiones)
    {
        Lista clavesGeneradas = a_ej10_generarlistaclaves(cantidaclavesagenerar, valorminimo, valormaximo);
        ArbolAVL avl = a_ej10_crearAVL(clavesGeneradas);
        ArbolBinarioBusqueda abb = a_ej10_crearABB(clavesGeneradas);
        // mostrarArbol(avl_raiz(avl));
        printf("---------------\n");
        // mostrarArbol(abb_raiz(abb));
        int diferenciaAltura = a_ej10_difalturas(abb, avl);
        l_agregar(resultado, te_crear(diferenciaAltura));
        i++;
    }
    return resultado;
}

void testPt2()
{
    clearScreen();
    ArbolBinario arbol = a_crear();
    char tipo;
    arbol = cargarArbol(&tipo);

    mostrarArbol(a_raiz(arbol), tipo);

    printf("\nArbol cargado exitosamente\n");
    printf("Tipo de elementos: %c\n", tipo);

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Ver hojas\n");
        printf("| 2. Ver interiores\n");
        printf("| 3. Buscar clave\n");
        printf("| 4. Volver\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;

        while (scanf("%d", &opcion) != 1)
        {
            printf("\nError: Ingresa un número válido para la opción: ");
            while (getchar() != '\n')
            {
                // clear input buffer
            }
        }

        switch (opcion)
        {
        case 1:
            clearScreen();
            Lista hojas = a_ej2_hojas(arbol);
            Iterador iterador_hojas = iterador(hojas);
            while (hay_siguiente(iterador_hojas))
            {
                TipoElemento elemento_hojas = siguiente(iterador_hojas);

                // check if tipo is number or letter
                if (tipo == 'n')
                    printf("\n| Clave: %d, Posicion: %p", elemento_hojas->clave, (void *)elemento_hojas->valor);
                else
                    printf("\n| Clave: %c, Posicion: %p", (char)elemento_hojas->clave, (void *)elemento_hojas->valor);
            }

            waitForKey();
            break;
        case 2:
            clearScreen();
            Lista interiores = a_ej2_interiores(arbol);
            l_mostrar(interiores);

            Iterador iterador_interiores = iterador(interiores);
            while (hay_siguiente(iterador_interiores))
            {
                TipoElemento elemento_interiores = siguiente(iterador_interiores);

                // check if tipo is number or letter
                if (tipo == 'n')
                    printf("\n| Clave: %d, Posicion: %p", elemento_interiores->clave, (void *)elemento_interiores->valor);
                else
                    printf("\n| Clave: %c, Posicion: %p", (char)elemento_interiores->clave, (void *)elemento_interiores->valor);
            }

            waitForKey();
            break;
        case 3:
            clearScreen();

            int clave;

            printf("\nIngrese la clave a buscar: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &clave) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        clave = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            printf("\nClave a buscar: %d", clave);
            printf("\nTipo de clave: %c\n", tipo);
            printf("\n");

            Lista igual = a_ej2_buscarclave(arbol, (int)clave);
            Iterador iteIg = iterador(igual);
            while (hay_siguiente(iteIg))
            {
                TipoElemento ele = siguiente(iteIg);

                if (tipo == 'n')
                {
                    printf("\n| Clave: %d, Posicion: %p", ele->clave, (void *)ele->valor);
                }
                else if (tipo == 'l')
                {
                    printf("\n| Clave: %c, Posicion: %p", (char)ele->clave, (void *)ele->valor);
                }
            }

            waitForKey();
            break;
        case 4:
            clearScreen();
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

void testPt3()
{
    clearScreen();
    ArbolBinario arbol = a_crear();
    char tipo;
    arbol = cargarArbol(&tipo);

    mostrarArbol(a_raiz(arbol), tipo);

    printf("\nArbol cargado exitosamente\n");
    printf("Tipo de elementos: %c\n", tipo);

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Buscar padre de un nodo\n");
        printf("| 2. Buscar hijos de un nodo\n");
        printf("| 3. Buscar hermano de un nodo\n");
        printf("| 4. Buscar nivel de un nodo\n");
        printf("| 5. Buscar altura de una rama\n");
        printf("| 6. Listar nodos de un nivel\n");
        printf("| 7. Volver\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;

        while (scanf("%d", &opcion) != 1)
        {
            printf("\nError: Ingresa un número válido para la opción: ");
            while (getchar() != '\n')
            {
                // clear input buffer
            }
        }

        switch (opcion)
        {
        case 1:
            clearScreen();
            int clavePadre;
            printf("\nIngrese la clave del nodo hijo: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &clavePadre) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        clavePadre = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            if (tipo == 'n')
                printf("\nClave del nodo hijo: %d", clavePadre);
            else
                printf("\nClave del nodo hijo: %c", (char)clavePadre);

            printf("\nTipo de clave: %c\n", tipo);

            int resultado = a_ej3_clavepadre(arbol, clavePadre);
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
                if (tipo == 'n')
                    printf("\nEl padre del nodo %d, es %d\n", clavePadre, resultado);
                else
                    printf("\nEl padre del nodo %c, es %c\n", (char)clavePadre, (char)resultado);
            }

            waitForKey();
            break;
        case 2:
            clearScreen();
            int clavePadreHijos;
            printf("\nIngrese la clave del nodo padre: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &clavePadreHijos) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        clavePadreHijos = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            if (tipo == 'n')
                printf("\nClave del nodo padre: %d", clavePadreHijos);
            else
                printf("\nClave del nodo padre: %c", (char)clavePadreHijos);
            printf("\nTipo de clave: %c\n", tipo);

            Lista hijos = a_ej3_hijos(arbol, clavePadreHijos);
            if (l_es_vacia(hijos))
            {
                printf("La clave era una hoja, por lo tanto no tenia hijos\n");
            }
            else
            {
                if (tipo == 'n')
                    printf("\nLos hijos del nodo %d son: ", clavePadreHijos);
                else
                    printf("\nLos hijos del nodo %c son: ", (char)clavePadreHijos);

                Iterador iteHijos = iterador(hijos);
                while (hay_siguiente(iteHijos))
                {
                    TipoElemento ele = siguiente(iteHijos);

                    if (tipo == 'n')
                        printf("\n| Clave: %d, Posicion: %p", ele->clave, (void *)ele->valor);
                    else
                        printf("\n| Clave: %c, Posicion: %p", (char)ele->clave, (void *)ele->valor);
                }
            }

            waitForKey();
            break;
        case 3:
            clearScreen();
            int claveHermano;
            printf("\nIngrese la clave del nodo: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &claveHermano) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        claveHermano = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            if (tipo == 'n')
                printf("\nClave del nodo: %d", claveHermano);
            else
                printf("\nClave del nodo: %c", (char)claveHermano);
            printf("\nTipo de clave: %c\n", tipo);

            int resultadoHermano = a_ej3_hermano(arbol, claveHermano);
            if (resultadoHermano == -999)
            {
                printf("Hay 2 posibles opciones..\n");

                if (tipo == 'n')
                    printf("1. El hijo con la clave %d, no tiene hermano\n", claveHermano);
                else
                    printf("1. El hijo con la clave %c, no tiene hermano\n", (char)claveHermano);

                if (tipo == 'n')
                    printf("2. No existe un hijo con la clave %d, por lo tanto no existe un hermano\n", claveHermano);
                else
                    printf("2. No existe un hijo con la clave %c, por lo tanto no existe un hermano\n", (char)claveHermano);
            }
            else
            {
                if (tipo == 'n')
                    printf("El hijo %d, tiene como hermano a %d \n", claveHermano, resultadoHermano);
                else
                    printf("El hijo %c, tiene como hermano a %c \n", (char)claveHermano, (char)resultadoHermano);
            }

            waitForKey();
            break;

        case 4:
            clearScreen();
            int claveNivel;
            printf("\nIngrese la clave del nodo: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &claveNivel) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        claveNivel = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            if (tipo == 'n')
                printf("\nClave del nodo: %d", claveNivel);
            else
                printf("\nClave del nodo: %c", (char)claveNivel);
            printf("\nTipo de clave: %c\n", tipo);

            int resultadoNivel = a_ej3_nivel(arbol, claveNivel);
            if (resultadoNivel == -1)
            {
                if (tipo == 'n')
                    printf("No se encontro la clave %d en el arbol\n", claveNivel);
                else
                    printf("No se encontro la clave %c en el arbol\n", (char)claveNivel);
            }
            else if (resultadoNivel == 0)
            {
                if (tipo == 'n')
                    printf("El nodo con la clave %d, se encuentra en la raiz..\n", claveNivel);
                else
                    printf("El nodo con la clave %c, se encuentra en la raiz..\n", (char)claveNivel);
            }
            else if (tipo == 'n')
                printf("El nodo con la clave %d, se encuentra en el nivel %d\n", claveNivel, resultadoNivel);
            else
                printf("El nodo con la clave %c, se encuentra en el nivel %d\n", (char)claveNivel, resultadoNivel);

            waitForKey();
            break;

        case 5:
            clearScreen();
            int claveAltura;
            printf("\nIngrese la clave del nodo: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &claveAltura) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        claveAltura = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            if (tipo == 'n')
                printf("\nClave del nodo: %d", claveAltura);
            else
                printf("\nClave del nodo: %c", (char)claveAltura);
            printf("\nTipo de clave: %c\n", tipo);

            int resultadoAltura = a_ej3_alturarama(arbol, claveAltura);
            if (resultadoAltura == -1)
            {
                printf("No se encontro la clave en el arbol\n");
            }
            else if (resultadoAltura == 0)
            {
                printf("La clave enviada es la raiz del arbol, por lo no tiene padre\n");
            }
            else
            {
                if (tipo == 'n')
                    printf("La altura de la rama con la clave %d, es %d\n", claveAltura, resultadoAltura);
                else
                    printf("La altura de la rama con la clave %c, es %d\n", (char)claveAltura, resultadoAltura);
            }

            waitForKey();
            break;

        case 6:
            clearScreen();
            int nivel;
            printf("\nIngrese el nivel a buscar: ");
            while (1)
            {
                if (scanf("%d", &nivel) == 1)
                {
                    break;
                }
                else
                {
                    printf("\nError: Ingresa un número válido para el nivel: ");
                    while (getchar() != '\n')
                        ;
                }
            }

            printf("\nNivel a buscar: %d\n", nivel);

            Lista nodosNivel = a_ej3_clavesmismonivel(arbol, nivel);
            // l_mostrar(nodosNivel);

            Iterador iterador_nodosNivel = iterador(nodosNivel);
            while (hay_siguiente(iterador_nodosNivel))
            {
                TipoElemento elemento_nodosNivel = siguiente(iterador_nodosNivel);

                // check if tipo is number or letter
                if (tipo == 'n')
                    printf("\n| Clave: %d, Posicion: %p", elemento_nodosNivel->clave, (void *)elemento_nodosNivel->valor);
                else
                    printf("\n| Clave: %c, Posicion: %p", (char)elemento_nodosNivel->clave, (void *)elemento_nodosNivel->valor);
            }

            waitForKey();
            break;

        case 7:
            clearScreen();
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

void testPt4()
{
    clearScreen();
    ArbolBinario arbol = a_crear();
    char tipo;
    arbol = cargarArbol(&tipo);

    mostrarArbol(a_raiz(arbol), tipo);

    printf("\nArbol cargado exitosamente\n");
    printf("Tipo de elementos: %c\n", tipo);

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Ver anchura de un arbol\n");
        printf("| 2. Ver cantidad de hojas (arbol n-ario)\n");
        printf("| 3. ¿Son similares dos arboles? (estructura)\n");
        printf("| 4. Ver padre de un nodo\n");
        printf("| 5. Ver hermanos de un nodo\n");
        printf("| 6. Volver\n");
        printf("+------------------------------------------------------------------------------------------+\n");

        printf("\nIngrese una opcion: ");
        int opcion;

        while (scanf("%d", &opcion) != 1)
        {
            printf("\nError: Ingresa un número válido para la opción: ");
            while (getchar() != '\n')
            {
                // clear input buffer
            }
        }

        switch (opcion)
        {
        case 1:
            clearScreen();
            Lista nodos = a_ej4_anchura(arbol);
            Iterador iterador_nodos = iterador(nodos);
            l_mostrar(nodos);
            while (hay_siguiente(iterador_nodos))
            {
                TipoElemento elemento_nodos = siguiente(iterador_nodos);

                // check if tipo is number or letter
                if (tipo == 'n')
                    printf("\n| Clave: %d, Posicion: %p", elemento_nodos->clave, (void *)elemento_nodos->valor);
                else
                    printf("\n| Clave: %c, Posicion: %p", (char)elemento_nodos->clave, (void *)elemento_nodos->valor);
            }
            waitForKey();
            break;
        case 2:
            clearScreen();
            int cantidadHojas = a_ej4_q_hojas(arbol);
            printf("\nCantidad de hojas en el arbol: %d\n", cantidadHojas);
            waitForKey();
            break;
        case 3:
            clearScreen();
            ArbolBinario arbol2 = a_crear();
            char tipo2;
            arbol2 = cargarArbol(&tipo2);

            printf("1. Arbol 1\n");
            mostrarArbol(a_raiz(arbol), tipo);

            printf("\n2. Arbol 2\n");
            mostrarArbol(a_raiz(arbol2), tipo2);

            bool resultado = a_ej4_similares(arbol, arbol2);
            if (resultado)
            {
                printf("\nLos arboles son similares\n");
            }
            else
            {
                printf("\nLos arboles no son similares\n");
            }

            waitForKey();
            break;
        case 4:
            clearScreen();
            int clavePadre;
            printf("\nIngrese la clave del nodo hijo: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &clavePadre) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        clavePadre = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            if (tipo == 'n')
                printf("\nClave del nodo hijo: %d", clavePadre);
            else
                printf("\nClave del nodo hijo: %c", (char)clavePadre);

            printf("\nTipo de clave: %c\n", tipo);

            TipoElemento resultadoPadre = a_ej4_padre(arbol, clavePadre);
            if (resultadoPadre == NULL)
            {
                printf("El hijo no existe en el arbol, por lo tanto no se pudo buscar el padre\n");
            }
            else
            {
                if (tipo == 'n')
                    printf("\nEl padre del nodo %d, es %d\n", clavePadre, resultadoPadre->clave);
                else
                    printf("\nEl padre del nodo %c, es %c\n", (char)clavePadre, (char)resultadoPadre->clave);
            }

            waitForKey();
            break;
        case 5:
            clearScreen();
            int claveHermano;
            printf("\nIngrese la clave del nodo: ");
            while (1)
            {
                if (tipo == 'n')
                {
                    if (scanf("%d", &claveHermano) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un número válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else if (tipo == 'l')
                {
                    char temp;
                    if (scanf(" %c", &temp) == 1)
                    {
                        claveHermano = (int)toupper(temp);
                        break;
                    }
                    else
                    {
                        printf("\nError: Ingresa un carácter válido para la clave: ");
                        while (getchar() != '\n')
                            ;
                    }
                }
                else
                {
                    printf("\nError: Tipo de clave no válido. Debe ser 'n' o 'l'.");
                }
            }

            if (tipo == 'n')
                printf("\nClave del nodo: %d", claveHermano);
            else
                printf("\nClave del nodo: %c", (char)claveHermano);
            printf("\nTipo de clave: %c\n", tipo);

            Lista resultadoHermano = a_ej4_hermanos(arbol, claveHermano);
            if (l_es_vacia(resultadoHermano))
            {
                printf("Hay 2 posibles opciones..\n");

                if (tipo == 'n')
                    printf("1. El hijo con la clave %d, no tiene hermano\n", claveHermano);
                else
                    printf("1. El hijo con la clave %c, no tiene hermano\n", (char)claveHermano);

                if (tipo == 'n')
                    printf("2. No existe un hijo con la clave %d, por lo tanto no existe un hermano\n", claveHermano);
                else
                    printf("2. No existe un hijo con la clave %c, por lo tanto no existe un hermano\n", (char)claveHermano);
            }
            else
            {
                if (tipo == 'n')
                    printf("El hijo %d, tiene como hermano(s) a: ", claveHermano);
                else
                    printf("El hijo %c, tiene como hermano(s) a: ", (char)claveHermano);
            }

            Iterador iteHermanos = iterador(resultadoHermano);
            while (hay_siguiente(iteHermanos))
            {
                TipoElemento ele = siguiente(iteHermanos);

                if (tipo == 'n')
                    printf("\n| Clave: %d, Posicion: %p", ele->clave, (void *)ele->valor);
                else
                    printf("\n| Clave: %c, Posicion: %p", (char)ele->clave, (void *)ele->valor);
            }

            waitForKey();
            break;
        case 6:
            clearScreen();
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

int main()
{
    srand(time(NULL));

    // clearScreen();
    printf("Archivo compilado exitosamente\n");
    printf("Esto es unicamente para comprobar que la compilacion fue exitosa\n");

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Ver complejidad algoritmica de cada punto\n");
        printf("| 2. Probar funciones del punto 2\n");
        printf("| 3. Probar funciones del punto 3\n");
        printf("| 4. Probar funciones del punto 4\n");
        printf("| 5. Probar funciones del punto 5\n");
        printf("| 6. Probar funciones del punto 6\n");
        printf("| 7. Probar funciones del punto 7\n");
        printf("| 8. Salir\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;

        while (scanf("%d", &opcion) != 1)
        {
            printf("\nError: Ingresa un número válido para la opción: ");
            while (getchar() != '\n')
            {
                // clear input buffer
            }
        }

        switch (opcion)
        {
        case 1:
            clearScreen();
            // verComplejidades();
            waitForKey();
            break;
        case 2:
            testPt2();
            break;
        case 3:
            testPt3();
            break;
        case 4:
            testPt4();
            break;
        case 5:
            // testPt5();
            break;
        case 6:
            // testPt6();
            break;
        case 7:
            // testPt7();
            break;
        case 8:
            clearScreen();
            return 0;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }

    return 0;
}

// int main()
// {
//     srand(time(NULL));
//     ArbolBinario arbol = a_crear();
//     arbol = cargarArbol();
//     printf("----------------------\n");

//     // ArbolBinario arbol2 = a_crear();
//     // arbol2 = cargarArbol();
//     // Lista hojas = a_ej2_hojas(arbol);
//     // l_mostrar(hojas);
//     // printf("\n ----------------------------");
//     // Lista interiores = a_ej2_interiores(arbol);
//     // l_mostrar(interiores);
//     // printf("\n ----------------------------");
//     // Lista igual = a_ej2_buscarclave(arbol, 10);
//     // Iterador iteIg = iterador(igual);
//     // while (hay_siguiente(iteIg))
//     // {
//     //     TipoElemento ele = siguiente(iteIg);
//     //     printf("\n| Clave: %d, Posicion: %p", ele->clave, (void *)ele->valor);
//     // }>>
//     // ArbolBinario arbol2 = a_crear();
//     // arbol2 = cargarArbol();
//     // printf("\n ----------------------------");

//     // Lista hojas = a_ej2_hojas(arbol);
//     // l_mostrar(hojas);

//     // printf("\n ----------------------------");

//     // Lista interiores = a_ej2_interiores(arbol);
//     // l_mostrar(interiores);

//     // printf("\n ----------------------------");

//     // Lista igual = a_ej2_buscarclave(arbol, 10);
//     // Iterador iteIg = iterador(igual);
//     // while (hay_siguiente(iteIg))
//     // {
//     //     TipoElemento ele = siguiente(iteIg);
//     //     printf("\n| Clave: %d, Posicion: %p", ele->clave, (void *)ele->valor);
//     // }

//     // printf("\n ----------------------------");

//     // int hijo = 2;
//     // int resultado = a_ej3_clavepadre(arbol, hijo);
//     // if (resultado == -999)
//     // {
//     //     printf("El hijo no existe en el arbol, por lo tanto no se pudo buscar el padre\n");
//     // }
//     // else if (resultado == 999)
//     // {
//     //     printf("La clave enviada es la raiz del arbol, por lo no tiene padre\n");
//     // }
//     // else
//     // {
//     //     printf("El hijo %d, tiene como padre a %d \n", hijo, resultado);
//     // }
//     // printf("\n ----------------------------");

//     // int clavePadre = 10;
//     // Lista resu = a_ej3_hijos(arbol, clavePadre);
//     // if (l_es_vacia(resu))
//     // {
//     //     printf("La clave era una hoja, por lo tanto no tenia hijos\n");
//     // }
//     // else
//     // {
//     //     printf("El padre %d, tiene el(los) siguiente(s) hijo(s)..\n", clavePadre);
//     //     l_mostrar(resu);
//     // }

//     // printf("\n ----------------------------");

//     // int clave = 2;
//     // int resultado = a_ej3_hermano(arbol, clave);
//     // if (resultado == -999)
//     // {
//     //     printf("Hay 2 posibles opciones..\n");
//     //     printf("1 - El hijo con la clave %d, no tiene hermano\n", clave);
//     //     printf("2 - No existe un hijo con la clave %d, por lo tanto no existe un hermano\n", clave);
//     // }
//     // else
//     // {
//     //     printf("El hijo %d, tiene como hermano a %d \n", clave, resultado);
//     // }

//     // printf("\n ----------------------------");

//     // int clave = 5;
//     // int resultado = a_ej3_nivel(arbol, clave);
//     // if (resultado == -1)
//     // {
//     //     printf("El nodo con la clave %d, no se encuentra en el arbol..\n", clave);
//     // }
//     // else if (resultado == 0)
//     // {
//     //     printf("El nodo con la clave %d, se encuentra en la raiz..\n", clave);
//     // }
//     // else
//     //     printf("El nodo con la clave %d se encuentra en el nivel numero : %d..\n", clave, resultado);

//     // printf("\n ----------------------------");

//     // int clave = 150;
//     // int altura = a_ej3_alturarama(arbol, clave);
//     // if (altura == -1)
//     // {
//     //     printf("No se encontro la clave en el arbol\n");
//     // }
//     // else if (altura == 0)
//     // {
//     //     printf("el arbol esta vacio o es una hoja(altura 0) \n");
//     // }
//     // else
//     // {
//     //     printf("El nodo con la clave %d tiene una altura de: %d \n", clave, altura);
//     // }

//     // printf("\n ----------------------------");

//     // int nivel = 2;
//     // Lista lis = a_ej3_clavesmismonivel(arbol, nivel);
//     // printf("En el nivel: %d, se encuentran los siguientes Nodos: \n", nivel);
//     // l_mostrar(lis);

//     // printf("\n ----------------------------");

//     // Lista resu = a_ej4_anchura(arbol);
//     // l_mostrar(resu);

//     // printf("\n ----------------------------");

//     // int resultado = a_ej4_q_hojas(arbol);
//     // printf("La cantidad de hojas es %d\n", resultado);

//     // printf("\n ----------------------------");

//     // bool resultado = a_ej4_similares(arbol, arbol2);
//     // if (resultado)
//     // {
//     //     printf("Los arboles son similares\n");
//     // }
//     // else
//     //     printf("Los arboles no son similares\n");

//     // printf("\n ----------------------------"):
//     // int clave = 15; //pedir clave en el menu, validar que se encuentre en el arbol.
//     // TipoElemento resultadoEj4Pa = a_ej4_padre(arbol, clave);

//     // printf("\n ----------------------------"):

//     // printf("\n ----------------------------"):

//     // FALTA 4E

//     // printf("\n ----------------------------"):

//     // bool resultado = a_ej7_equivalente(arbol, arbol2);
//     // if (resultado)
//     // {
//     //     printf("Los arboles son equvalentes\n");
//     // }
//     // else
//     //     printf("Los arboles no son equivalentes\n");

//     // printf("\n ----------------------------"):

//     // int resultado8a = c_ej8_altura(arbol);
//     // printf("La altura del arbol n-ario es %i\n", resultado8a);

//     // printf("\n ----------------------------"):

//     // FALTA 8B

//     // printf("\n ----------------------------"):

//     // Lista resultadoEje8c = c_ej8_internos(arbol);
//     // printf("Los nodos internos son: \n");
//     // if (!l_es_vacia(resultadoEje8c))
//     // {
//     //     l_mostrar(resultadoEje8c);
//     // }
//     // else
//     //     printf("No hay nodos internos\n");

//     //int resultado8a = c_ej8_altura(arbol);
//     //printf("La altura del arbol n-ario es %i\n", resultado8a);
//     // printf("\n ----------------------------"):

//     // FALTA 8C

//     // printf("\n ----------------------------"):

//     // ArbolAVL arbolAvl = a_ej9_construiravl(arbol);
//     // int resultadoDiferenciaAltura = a_ej9_diferenciaalturas(arbol, arbolAvl);
//     // printf("La diferencia entre alturas considerando (ARBOL - ARBOL AVL) es..  %i\n", resultadoDiferenciaAltura);
//     // test ej8_nivel
//     // int clave=4;
//     // int nivel= c_ej8_nivel(arbol,clave);
//     // if(nivel== -1){
//     //     printf("No se encontró el nodo\n");
//     // }
//     // else{
//     //     printf("El nivel del nodo con clave: %d, es : %d \n",clave,nivel);
//     // }
//     int clave=3;
//     Lista list=a_ej4_hermanos(arbol,clave);
//     printf("Para la clave: %d, la lista de hermanos son: \n",clave);
//     if(l_es_vacia(list)){
//         printf("La clave no tiene ningun hermano\n");
//     }
//     l_mostrar(list);
//     //Lista lista = a_ej10_comparacionarboles(2,10,21,10);
//     // l_mostrar(lista);
//     // printf("\n ----------------------------"):

//     // Lista lista = a_ej10_comparacionarboles(2,10,21,10);
//     //  l_mostrar(lista);
//     return 0;
// }

// gcc -o output ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c ../libs/nodos/nodo.c ../libs/arboles/arbol-binario.c ../libs/colas/colas_arreglos.c ../libs/arboles/arbol-avl.c ../libs/arboles/arbol-binario-busqueda.c main.c