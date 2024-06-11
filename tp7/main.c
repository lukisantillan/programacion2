#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "../libs/conjuntos/conjuntos.h"
#include "../libs/listas/listas.h"

Conjunto rellenarConjuntos()
{
    Conjunto resu = cto_crear();
    int cantidad;
    printf("Ingrese cuantos elementos queres agregar al conjunto:   \n");
    scanf("%i", &cantidad);
    for (int i = 0; i < cantidad; i++)
    {
        int clave;
        printf("Ingrese la clave: \n");
        scanf("%i", &clave);
        while (cto_pertenece(resu, clave))
        {
            printf("Reingrese la clave [RECUERDE QUE NO TRABAJAMOS CON MULTICONJUNTOS, POR LO TANTO LAS CLAVES NO DEBEN REPETIRSE]: \n");
            scanf("%i", &clave);
        }

        TipoElemento ele = te_crear(clave);
        cto_agregar(resu, ele);
        if (cto_pertenece(resu, ele->clave))
        {
            printf("El elemento se agrego correctamente\n");
        }
        else
        {
            printf("Hubo un error al agregar el elemento\n");
        }
    }
    return resu;
}

// Punto2
bool verificarUnion(Conjunto c1, Conjunto c2, Conjunto conjUnion)
{
    int tamañoC1 = cto_cantidad_elementos(c1);
    int tamañoC2 = cto_cantidad_elementos(c2);
    int i = 1;
    TipoElemento ele;
    while (i <= tamañoC1)
    {
        ele = cto_recuperar(c1, i);
        if (!cto_pertenece(conjUnion, ele->clave))
        {
            return false;
        }
        i++;
    }

    i = 1;

    while (i <= tamañoC2)
    {
        ele = cto_recuperar(c2, i);
        if (!cto_pertenece(conjUnion, ele->clave))
        {
            return false;
        }
        i++;
    }

    return true;
}

bool verificarInterseccion(Conjunto c1, Conjunto c2, Conjunto conjInter)
{
    int tamañoC1 = cto_cantidad_elementos(c1);
    int i = 1;
    TipoElemento ele;
    while (i <= tamañoC1)
    {
        ele = cto_recuperar(c1, i);
        if (cto_pertenece(c2, ele->clave) && !cto_pertenece(conjInter, ele->clave))
        {
            return false;
        }
        if (!cto_pertenece(c2, ele->clave) && cto_pertenece(conjInter, ele->clave))
        {
            return false;
        }

        i++;
    }
    return true;
}

bool verificarDiferencia(Conjunto c1, Conjunto c2, Conjunto conjDif)
{
    int tamañoC1 = cto_cantidad_elementos(c1);
    int i = 1;
    TipoElemento ele;
    while (i <= tamañoC1)
    {
        ele = cto_recuperar(c1, i);
        if (cto_pertenece(c2, ele->clave) && cto_pertenece(conjDif, ele->clave))
        {
            return false;
        }
        i++;
    }
    return true;
}

// Punto 3
Conjunto interseccionColeccion(Lista coleccion)
{
    Iterador ite = iterador(coleccion);
    TipoElemento ele = siguiente(ite);
    if (ele == NULL)
    {
        Conjunto vacio = cto_crear();
        return vacio; // Devuelve un conjunto vacío si la colección está vacía
    }
    Conjunto resultado = *(Conjunto *)ele->valor;

    while (hay_siguiente(ite))
    {
        ele = siguiente(ite);
        if (ele == NULL || ele->valor == NULL)
        {
            continue; // Salta los elementos nulos
        }
        Conjunto conj = *(Conjunto *)ele->valor;
        Conjunto temp = cto_interseccion(resultado, conj);
        free(resultado);
        resultado = temp;
    }
    return resultado;
}

Conjunto unionColeccion(Lista coleccion)
{
    Iterador ite = iterador(coleccion);
    TipoElemento ele;
    Conjunto resultado = cto_crear();
    while (hay_siguiente(ite))
    {
        ele = siguiente(ite);
        Conjunto conj = *(Conjunto *)ele->valor;
        Conjunto temp = cto_union(resultado, conj);
        printf("\t\t-----\n");
        cto_mostrar(temp);
        printf("\t\t-----\n");
        resultado = temp;
    }
    return resultado;
}

// Punto 4
bool transitividad(Conjunto a, Conjunto b, Conjunto c)
{
    int longitud = cto_cantidad_elementos(b);
    int i = 1;
    TipoElemento ele;
    while (i < longitud)
    {
        // Primero valido que todos los elementos de B, pertenezcan a C
        ele = cto_recuperar(b, i);
        if (!cto_pertenece(c, ele->clave))
        {
            return false;
        }
        i++;
    }

    i = 1;
    longitud = cto_cantidad_elementos(a);
    while (i < longitud)
    {
        // valido que los de A, pertenezcan a B, al ya estar validado que B pertenece a C, los de A tambien pertenecerian a C
        ele = cto_recuperar(a, i);
        if (!cto_pertenece(b, ele->clave))
        {
            return false;
        }
        i++;
    }
    return true;
}

// Punto5
Conjunto diferenciaSimetrica(Conjunto c1, Conjunto c2)
{
    Conjunto resultado = cto_crear();
    int longitud = cto_cantidad_elementos(c1);
    int i = 1;
    TipoElemento ele;
    while (i <= longitud)
    {
        ele = cto_recuperar(c1, i);
        if (!cto_pertenece(c2, ele->clave))
        {
            cto_agregar(resultado, ele);
        }
        i++;
    }

    i = 1;
    longitud = cto_cantidad_elementos(c2);
    while (i <= longitud)
    {
        ele = cto_recuperar(c2, i);
        if (!cto_pertenece(c1, ele->clave))
        {
            cto_agregar(resultado, ele);
        }
        i++;
    }
    return resultado;
}

// Punto 6
bool subconjuntoPropioAux(Conjunto a, Conjunto b)
{
    int longitud = cto_cantidad_elementos(a);
    int i = 1;
    TipoElemento ele;
    while (i <= longitud)
    {
        ele = cto_recuperar(a, i);
        if (!cto_pertenece(b, ele->clave))
        {
            return false;
        }
        i++;
    }
    // CHEQUEO SI B TIENE ELEMENTOS QUE NO CONTENGA A.
    Conjunto checkB = diferenciaSimetrica(a, b);
    if (cto_es_vacio(checkB))
    {
        return false;
    }
    return true;
}

void subConjuntoPropioCheck(Conjunto a, Conjunto b)
{
    bool checkConjuntoA = subconjuntoPropioAux(a, b);
    bool checkConjuntoB = subconjuntoPropioAux(b, a);
    if (checkConjuntoA || checkConjuntoB)
    {
        if (checkConjuntoA)
        {
            printf("EL CONJUNTO A ES SUBCONJUNTO DE B, PERO A <> B\n");
        }
        else if (checkConjuntoB)
        {
            printf("EL CONJUNTO B ES SUBCONJUNTO DE A, PERO B <> A\n");
        }
    }
    else
        printf("NINGUN CONJUNTO ES SUBCONJUNTO DEL OTRO \n");
}

// Punto 7
int es_subconjunto_total(Conjunto a, Conjunto b)
{
    for (int i = 1; i <= cto_cantidad_elementos(a); i++)
    {
        if (!cto_pertenece(b, cto_recuperar(a, i)->clave))
        {
            return 0;
        }
    }
    return 1;
}

int es_subconjunto_parcial(Conjunto a, Conjunto b)
{
    int cuenta = 0;
    int tamano = cto_cantidad_elementos(a);
    for (int i = 1; i <= tamano; i++)
    {
        if (cto_pertenece(b, cto_recuperar(a, i)->clave))
        {
            cuenta++;
        }
    }
    return cuenta >= (tamano + 1) / 2; // La mitad redondeada hacia arriba
}

void determinar_subconjuntos(Conjunto a, Conjunto b, Conjunto c)
{
    if (es_subconjunto_total(a, b))
    {
        printf("A es un subconjunto total de B\n");
    }
    else if (es_subconjunto_parcial(a, b))
    {
        printf("A es un subconjunto parcial de B\n");
    }
    if (es_subconjunto_total(a, c))
    {
        printf("A es un subconjunto total de C\n");
    }
    else if (es_subconjunto_parcial(a, c))
    {
        printf("A es un subconjunto parcial de C\n");
    }
    if (es_subconjunto_total(b, a))
    {
        printf("B es un subconjunto total de A\n");
    }
    else if (es_subconjunto_parcial(b, a))
    {
        printf("B es un subconjunto parcial de A\n");
    }
    if (es_subconjunto_total(b, c))
    {
        printf("B es un subconjunto total de C\n");
    }
    else if (es_subconjunto_parcial(b, c))
    {
        printf("B es un subconjunto parcial de C\n");
    }
    if (es_subconjunto_total(c, a))
    {
        printf("C es un subconjunto total de A\n");
    }
    else if (es_subconjunto_parcial(c, a))
    {
        printf("C es un subconjunto parcial de A\n");
    }
    if (es_subconjunto_total(c, b))
    {
        printf("C es un subconjunto total de B\n");
    }
    else if (es_subconjunto_parcial(c, b))
    {
        printf("C es un subconjunto parcial de B\n");
    }
}

// Punto 8
bool iguales(Conjunto a, Conjunto b)
{
    int longitudA = cto_cantidad_elementos(a);
    int longitudB = cto_cantidad_elementos(b);
    if (longitudA != longitudB)
    {
        return false;
    }
    int i = 1;
    while (i <= longitudA)
    {
        if (!cto_pertenece(b, cto_recuperar(a, i)->clave))
        {
            return false;
        }
        i++;
    }
    return true;
}

int main()
{
    // // PUNTO 2 A
    Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();
    // Conjunto unionUnoDos = cto_union(uno,dos);
    // cto_mostrar(unionUnoDos);

    // bool resultadopt2Union = verificarUnion(uno,dos,unionUnoDos);
    // if (resultadopt2Union)
    // {
    //     printf("La union se realizo correctamente\n");
    // } else printf("La union fallo\n");

    // // PUNTO 2 B
    // Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();
    // Conjunto interseccionUnoDos = cto_interseccion(uno,dos);
    // cto_mostrar(interseccionUnoDos);

    // bool resultadopt2Interseccion = verificarInterseccion(uno,dos,interseccionUnoDos);
    // if (resultadopt2Interseccion)
    // {
    //     printf("La interseccion se realizo correctamente\n");
    // } else printf("La interseccion fallo\n");

    // // PUNTO 2 C
    // Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();
    // Conjunto difereciaUnoDos = cto_diferencia(uno,dos);
    // cto_mostrar(difereciaUnoDos);

    // bool resultadopt2Diferencia = verificarDiferencia(uno,dos,difereciaUnoDos);
    // if (resultadopt2Diferencia)
    // {
    //     printf("La diferecia se realizo correctamente\n");
    // } else printf("La diferecia fallo\n");

    // // PUNTO 3 UNION
    // Lista coleccion = l_crear();
    // int cantidad;
    // printf("Ingrese cuantos conjuntos queres agregar a la coleccion:   \n");
    // scanf("%d", &cantidad);

    // for (int i = 1; i <= cantidad; i++)
    // {
    //     Conjunto *conj = malloc(sizeof(Conjunto));
    //     *conj = rellenarConjuntos();
    //     TipoElemento ele = te_crear_con_valor(i, conj);
    //     l_agregar(coleccion, ele);
    //     printf("Conjunto con direccion : %p, agregado a la coleccion\n\n", ele->valor);
    // }
    // Conjunto resultadoPt3a = unionColeccion(coleccion);
    // cto_mostrar(resultadoPt3a);

    // // PUNTO 3 INTERSECCION
    // Lista coleccion = l_crear();
    // int cantidad;
    // printf("Ingrese cuantos conjuntos queres agregar a la coleccion:   \n");
    // scanf("%d", &cantidad);

    // for (int i = 1; i <= cantidad; i++)
    // {
    //     Conjunto *conj = malloc(sizeof(Conjunto));
    //     *conj = rellenarConjuntos();
    //     TipoElemento ele = te_crear_con_valor(i, conj);
    //     l_agregar(coleccion, ele);
    //     printf("Conjunto con direccion : %p, agregado a la coleccion\n\n", ele->valor);
    // }

    // Conjunto resultadoPt3b = interseccionColeccion(coleccion);
    // cto_mostrar(resultadoPt3b);

    // // PUNTO 4
    // Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();
    // Conjunto tres = rellenarConjuntos();

    // bool resultadopt4= transitividad(uno,dos,tres);
    // if (resultadopt4)
    // {
    //     printf("Se cumple la propiedad de transitividad\n");
    // } else printf("No hay transitividad\n");

    // // PUNTO 5
    // Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();

    // Conjunto resultadopt5= diferenciaSimetrica(uno,dos);
    // cto_mostrar(resultadopt5);

    // // PUNTO 6
    // Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();
    // subConjuntoPropioCheck(uno,dos);

    // // PUNTO 7
    // Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();
    // Conjunto tres = rellenarConjuntos();
    // determinar_subconjuntos(uno, dos, tres);

    // // PUNTO 8
    // Conjunto uno = rellenarConjuntos();
    // Conjunto dos = rellenarConjuntos();

    // bool resultadopt8 = iguales(uno,dos);
    // if (resultadopt8)
    // {
    //     printf("Los Conjuntos son iguales sin importar la posicion\n");
    // } else {printf("Los conjuntos son diferentes\n");}

    return 0;
}
