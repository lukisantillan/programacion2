#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "../libs/conjuntos/conjuntos.h"


//Punto2 - prototipos 
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

    i = 1

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
        if (cto_pertenece(c2, ele->clave) && !cto_pertenece(conjDif, ele->clave))
        {
            return false;
        } 
        if (!cto_pertenece(c2, ele->clave) && cto_pertenece(conjDif, ele->clave))
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

//Punto 3- NO SE SI SE HACE PORQUE YA ESTA EN LAS TADS.

//Punto 4
bool transitividad(Conjunto a, Conjunto b, Conjunto c){
    int longitud = cto_cantidad_elementos(b);
    int i = 1;
    TipoElemento ele;
    while (i < longitudB)
    {
        //Primero valido que todos los elementos de B, pertenezcan a C
        ele = cto_recuperar(b, i);
        if (!cto_pertenece(c, ele->clave))
        {
            return false;
        }
        i++;
    }
    
    int i = 1;
    longitud = cto_cantidad_elementos(a);
    while (i < longitud)
    {
        //valido que los de A, pertenezcan a B, al ya estar validado que B pertenece a C, los de A tambien pertenecerian a C
        ele = cto_recuperar(a,i);
        if (!cto_pertenece(b, ele->clave))
        {
            return false;
        }
        i++;
    }
    return true;
}

//Punto5
Conjunto diferenciaSimetrica(Conjunto c1, Conjunto c2){
    Conjunto resultado = cto_crear();
    int longitud = cto_cantidad_elementos(c1);
    int i = 1;
    TipoElemento ele;
    while (i <= longitud)
    {
        ele = cto_recuperar(c1,i);
        if (!cto_pertenece(c2, ele->clave))
        {
            cto_agregar(resultado, ele);
        }
        i++;
    }
    
    int i = 1;
    longitud = cto_cantidad_elementos(c2);
    while (i <= longitud)
    {
        ele = cto_recuperar(c2,i);
        if (!cto_pertenece(c1, ele->clave))
        {
            cto_agregar(resultado,ele);
        }
        i++;   
    }
    return resultado;
}

//Punto 6
bool subconjuntoPropioAux(Conjunto a, Conjunto b){
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
    //CHEQUEO SI B TIENE ELEMENTOS QUE NO CONTENGA A.
    Conjunto checkB = diferenciaSimetrica(a, b);
    if (cto_es_vacio(checkB))
    {
        return false;
    }
    return true;
}

bool subConjuntoPropioCheck(Conjunto a, Conjunto b){
    bool checkConjuntoA = subconjuntoPropioAux(a,b);
    bool checkConjuntoB = subconjuntoPropioAux(b,a);
    if (checkConjuntoA || checkConjuntoB)
    {
        if (checkConjuntoA)
        {
            printf("EL CONJUNTO A ES SUBCONJUNTO DE B, PERO A <> B\n");
            return true;
        } else if (checkConjuntoB)
        {
            printf("EL CONJUNTO B ES SUBCONJUNTO DE A, PERO B <> A\n");
            return true;
        }
    }
    printf("NINGUN CONJUNTO ES SUBCONJUNTO DEL OTRO \n");
    return false;
    
}