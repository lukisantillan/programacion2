#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "../libs/conjuntos/conjuntos.h"
#include "../libs/listas/listas.h"

// Funciones auxiliares
void verComplejidades()
{
    printf(" Complejidad de los ejercicios dados\n");
    printf("------------------------------------------\n");
    printf("Complejidad ejercicio 6 (Ver si un conjunto es subconjunto del otro):\n");
    printf("Implementado con listas y utilizando lista con arreglos la complejidad es O(n)\n");
    printf("Implementado con listas y utilizando lista con punteros o cursores la complejidad es O(n^2)\n");
    printf("Implementado con AVL y la complejidad es O(n^2) si se utiliza listas con punteros o cursores ya que la función recupera del TAD, utiliza l_agregar\n");
    printf("Implementado con AVL y la complejidad es O(n) si se utiliza listas con arreglos ya que la función recupera del TAD, utiliza l_agregar\n");
    printf("------------------------------------------\n");
    printf("Complejidad ejercicio 7 (Ver si un conjunto es subconjunto total o parcial):\n");
    printf("Implementado con listas y utilizando lista con arreglos la complejidad es O(n)\n");
    printf("Implementado con listas y utilizando lista con punteros o cursores la complejidad es O(n^2)\n");
    printf("Implementado con AVL y la complejidad es O(n^2) si se utiliza listas con punteros o cursores ya que la función recupera del TAD, utiliza l_agregar\n");
    printf("Implementado con AVL y la complejidad es O(n) si se utiliza listas con arreglos ya que la función recupera del TAD, utiliza l_agregar\n");
    printf("------------------------------------------\n");
    printf("Complejidad ejercicio 8 (Ver si un conjunto es igual al otro sin importar la posicion):\n");
    printf("Implementado con listas y utilizando lista con arreglos la complejidad es O(n)\n");
    printf("Implementado con listas y utilizando lista con punteros o cursores la complejidad es O(n^2)\n");
    printf("Implementado con AVL y la complejidad es O(n^2) si se utiliza listas con punteros o cursores ya que la función recupera del TAD, utiliza l_agregar\n");
    printf("Implementado con AVL y la complejidad es O(n) si se utiliza listas con arreglos ya que la función recupera del TAD, utiliza l_agregar\n");
    printf("------------------------------------------\n");
}

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

Conjunto rellenarConjuntos()
{
    clearScreen();
    Conjunto resu = cto_crear();
    int cantidad;
    printf("Ingrese cuantos elementos queres agregar al conjunto: ");
    while (scanf("%d", &cantidad) != 1 || cantidad <= 0)
    {
        printf("Ingrese un numero valido: ");
        while (getchar() != '\n')
            ;
    }
    for (int i = 0; i < cantidad; i++)
    {
        int clave;
        printf("Ingrese la clave: ");
        while (scanf("%d", &clave) != 1)
        {
            printf("Ingrese un numero valido: ");
            while (getchar() != '\n')
                ;
        }
        while (cto_pertenece(resu, clave))
        {
            printf("Reingrese la clave [RECUERDE QUE NO TRABAJAMOS CON MULTICONJUNTOS, POR LO TANTO LAS CLAVES NO DEBEN REPETIRSE]: ");
            while (scanf("%d", &clave) != 1)
            {
                printf("Ingrese un numero valido: ");
                while (getchar() != '\n')
                    ;
            }
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
    int tamanoC1 = cto_cantidad_elementos(c1);
    int tamanoC2 = cto_cantidad_elementos(c2);
    int i = 1;
    TipoElemento ele;
    while (i <= tamanoC1)
    {
        ele = cto_recuperar(c1, i);
        if (!cto_pertenece(conjUnion, ele->clave))
        {
            return false;
        }
        i++;
    }

    i = 1;

    while (i <= tamanoC2)
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
    int tamanoC1 = cto_cantidad_elementos(c1);
    int i = 1;
    TipoElemento ele;
    while (i <= tamanoC1)
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
    int tamanoC1 = cto_cantidad_elementos(c1);
    int i = 1;
    TipoElemento ele;
    while (i <= tamanoC1)
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

bool verificarPertenencia(Conjunto c1, Conjunto c2)
{
    TipoElemento eleAux;
    int tamano = cto_cantidad_elementos(c1);
    int i = 1;
    while (i <= tamano)
    {
        eleAux = cto_recuperar(c1, i);
        if (!cto_pertenece(c2, eleAux->clave))
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
        return vacio;
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

void testPt2()
{
    clearScreen();
    Conjunto uno = rellenarConjuntos();
    Conjunto dos = rellenarConjuntos();

    printf("Conjunto 1: \n");
    cto_mostrar(uno);
    printf("Conjunto 2: \n");
    cto_mostrar(dos);

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Unir y verificar unión de dos conjuntos\n");
        printf("| 2. Intersectar y verificar intersección de dos conjuntos\n");
        printf("| 3. Diferenciar y verificar diferencia de dos conjuntos\n");
        printf("| 4. Verificar pertenencia de un conjunto a otro\n");
        printf("| 5. Volver al menu principal\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;

        while (scanf("%d", &opcion) != 1 || opcion < 1 || opcion > 5)
        {
            printf("Ingrese una opcion valida: ");
            while (getchar() != '\n')
                ;
        }

        switch (opcion)
        {
        case 1:
        {
            Conjunto unionUnoDos = cto_union(uno, dos);
            cto_mostrar(unionUnoDos);
            bool resultadopt2Union = verificarUnion(uno, dos, unionUnoDos);
            if (resultadopt2Union)
            {
                printf("La union se realizo correctamente\n");
            }
            else
                printf("La union fallo\n");

            waitForKey();
            break;
        }
        case 2:
        {
            Conjunto interseccionUnoDos = cto_interseccion(uno, dos);
            cto_mostrar(interseccionUnoDos);
            bool resultadopt2Interseccion = verificarInterseccion(uno, dos, interseccionUnoDos);
            if (resultadopt2Interseccion)
            {
                printf("La interseccion se realizo correctamente\n");
            }
            else
                printf("La interseccion fallo\n");

            waitForKey();
            break;
        }
        case 3:
        {
            Conjunto difereciaUnoDos = cto_diferencia(uno, dos);
            cto_mostrar(difereciaUnoDos);
            bool resultadopt2Diferencia = verificarDiferencia(uno, dos, difereciaUnoDos);
            if (resultadopt2Diferencia)
            {
                printf("La diferecia se realizo correctamente\n");
            }
            else
                printf("La diferecia fallo\n");

            waitForKey();
            break;
        }
        case 4:
        {
            bool resultadopt2PertenenciaA = verificarPertenencia(uno, dos);
            bool resultadopt2PertenenciaB  = verificarPertenencia(dos,uno);
            if (resultadopt2PertenenciaA)
            {
                printf("El conjunto 1 pertenece al conjunto 2\n");
            } else if (resultadopt2PertenenciaB)
            {
                printf("El conjunto 2 pertenece al conjunto 1\n");
            } else
                printf("Ningun conjunto pertenece al otro\n");
            waitForKey();
            break;
        }
        case 5:
        {
            return;
        }
        default:
            break;
        }
    }
}

void testPt3()
{
    clearScreen();
    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Unir y verificar unión de una colección de conjuntos\n");
        printf("| 2. Intersectar y verificar intersección de una colección de conjuntos\n");
        printf("| 3. Volver al menu principal\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;

        while (scanf("%d", &opcion) != 1 || opcion < 1 || opcion > 3)
        {
            printf("Ingrese una opcion valida: ");
            while (getchar() != '\n')
                ;
        }

        switch (opcion)
        {
        case 1:
        {
            Lista coleccion = l_crear();
            int cantidad;
            printf("Ingrese cuantos conjuntos queres agregar a la coleccion:   \n");
            while (scanf("%d", &cantidad) != 1 || cantidad <= 0)
            {
                printf("Ingrese un numero valido: ");
                while (getchar() != '\n')
                    ;
            }

            for (int i = 1; i <= cantidad; i++)
            {
                Conjunto *conj = malloc(sizeof(Conjunto));
                *conj = rellenarConjuntos();
                TipoElemento ele = te_crear_con_valor(i, conj);
                l_agregar(coleccion, ele);
            }

            Conjunto resultadoPt3a = unionColeccion(coleccion);
            cto_mostrar(resultadoPt3a);

            waitForKey();
            break;
        }
        case 2:
        {
            Lista coleccion = l_crear();
            int cantidad;
            printf("Ingrese cuantos conjuntos queres agregar a la coleccion:   \n");
            while (scanf("%d", &cantidad) != 1 || cantidad <= 0)
            {
                printf("Ingrese un numero valido: ");
                while (getchar() != '\n')
                    ;
            }

            for (int i = 1; i <= cantidad; i++)
            {
                Conjunto *conj = malloc(sizeof(Conjunto));
                *conj = rellenarConjuntos();
                TipoElemento ele = te_crear_con_valor(i, conj);
                l_agregar(coleccion, ele);
                printf("Conjunto con direccion : %p, agregado a la coleccion\n\n", ele->valor);
            }

            Conjunto resultadoPt3b = interseccionColeccion(coleccion);
            cto_mostrar(resultadoPt3b);

            waitForKey();
            break;
        }
        case 3:
            return;
        default:
            break;
        }
    }
}

void testPt4()
{
    clearScreen();
    Conjunto uno = rellenarConjuntos();
    Conjunto dos = rellenarConjuntos();
    Conjunto tres = rellenarConjuntos();

    bool resultadopt4 = transitividad(uno, dos, tres);
    if (resultadopt4)
    {
        printf("Se cumple la propiedad de transitividad\n");
    }
    else
        printf("No hay transitividad\n");

    waitForKey();
}

void testPt5()
{
    clearScreen();
    Conjunto uno = rellenarConjuntos();
    Conjunto dos = rellenarConjuntos();

    Conjunto resultadopt5 = diferenciaSimetrica(uno, dos);
    cto_mostrar(resultadopt5);

    waitForKey();
}

void testPt6()
{
    clearScreen();
    Conjunto uno = rellenarConjuntos();
    Conjunto dos = rellenarConjuntos();
    subConjuntoPropioCheck(uno, dos);

    waitForKey();
}

void testPt7()
{
    clearScreen();
    Conjunto uno = rellenarConjuntos();
    Conjunto dos = rellenarConjuntos();
    Conjunto tres = rellenarConjuntos();
    determinar_subconjuntos(uno, dos, tres);

    waitForKey();
}

void testPt8()
{
    clearScreen();
    Conjunto uno = rellenarConjuntos();
    Conjunto dos = rellenarConjuntos();

    bool resultadopt8 = iguales(uno, dos);
    if (resultadopt8)
    {
        printf("Los Conjuntos son iguales sin importar la posicion\n");
    }
    else
    {
        printf("Los conjuntos son diferentes\n");
    }

    waitForKey();
}

int main()
{
    // clearScreen();
    printf("Archivo compilado exitosamente\n");
    printf("Esto es unicamente para comprobar que la compilacion fue exitosa\n");

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Probar funciones del punto 2\n");
        printf("| 2. Probar funciones del punto 3\n");
        printf("| 3. Probar funciones del punto 4 ( Transitividad )\n");
        printf("| 4. Probar funciones del punto 5 ( Diferencia simetrica )\n");
        printf("| 5. Probar funciones del punto 6 ( Determinar subconjunto )\n");
        printf("| 6. Probar funciones del punto 7 ( Determinar subconjunto total - parcial )\n");
        printf("| 7. Probar funciones del punto 8 ( Determinar si son iguales )\n");
        printf("| 8. Ver complejidades\n");
        printf("| 9. Salir\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;

        while (scanf("%d", &opcion) != 1)
        {
            printf("\nError: Ingresa un número válido para la opción: ");
            while (getchar() != '\n')
                ;
        }

        switch (opcion)
        {
        case 1:
            testPt2();
            break;
        case 2:
            testPt3();
            break;
        case 3:
            testPt4();
            break;
        case 4:
            testPt5();
            break;
        case 5:
            testPt6();
            break;
        case 6:
            testPt7();
            break;
        case 7:
            testPt8();
            break;
        case 8:
            verComplejidades();
            break;
        case 9:
            clearScreen();
            return 0;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }

    // // // PUNTO 2 A
    // Conjunto uno = rellenarConjuntos();
    // // Conjunto dos = rellenarConjuntos();
    // // Conjunto unionUnoDos = cto_union(uno,dos);
    // // cto_mostrar(unionUnoDos);

    // // bool resultadopt2Union = verificarUnion(uno,dos,unionUnoDos);
    // // if (resultadopt2Union)
    // // {
    // //     printf("La union se realizo correctamente\n");
    // // } else printf("La union fallo\n");

    // // // PUNTO 2 B
    // // Conjunto uno = rellenarConjuntos();
    // // Conjunto dos = rellenarConjuntos();
    // // Conjunto interseccionUnoDos = cto_interseccion(uno,dos);
    // // cto_mostrar(interseccionUnoDos);

    // // bool resultadopt2Interseccion = verificarInterseccion(uno,dos,interseccionUnoDos);
    // // if (resultadopt2Interseccion)
    // // {
    // //     printf("La interseccion se realizo correctamente\n");
    // // } else printf("La interseccion fallo\n");

    // // // PUNTO 2 C
    // // Conjunto uno = rellenarConjuntos();
    // // Conjunto dos = rellenarConjuntos();
    // // Conjunto difereciaUnoDos = cto_diferencia(uno,dos);
    // // cto_mostrar(difereciaUnoDos);

    // // bool resultadopt2Diferencia = verificarDiferencia(uno,dos,difereciaUnoDos);
    // // if (resultadopt2Diferencia)
    // // {
    // //     printf("La diferecia se realizo correctamente\n");
    // // } else printf("La diferecia fallo\n");

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

    // // // PUNTO 3 INTERSECCION
    // // Lista coleccion = l_crear();
    // // int cantidad;
    // // printf("Ingrese cuantos conjuntos queres agregar a la coleccion:   \n");
    // // scanf("%d", &cantidad);

    // // for (int i = 1; i <= cantidad; i++)
    // // {
    // //     Conjunto *conj = malloc(sizeof(Conjunto));
    // //     *conj = rellenarConjuntos();
    // //     TipoElemento ele = te_crear_con_valor(i, conj);
    // //     l_agregar(coleccion, ele);
    // //     printf("Conjunto con direccion : %p, agregado a la coleccion\n\n", ele->valor);
    // // }

    // // Conjunto resultadoPt3b = interseccionColeccion(coleccion);
    // // cto_mostrar(resultadoPt3b);

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
