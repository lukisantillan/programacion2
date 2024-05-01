#include <stdio.h>
#include <stdlib.h>
#include "TP_4_Colas.h"
// Funciónes Extras

void rellenarCola(Cola cola, int cantidadDeElementos)
{
    TipoElemento elemento;
    int clave;
    for (int i = 0; i < cantidadDeElementos; i++)
    {

        printf("Ingrese la clave: ");
        while (scanf("%d", &clave) != 1)
        {
            printf("\nError: Ingresa un número válido: ");
            while (getchar() != '\n')
            {
                // clear input buffer
            }
        }
        elemento = te_crear(clave);
        c_encolar(cola, elemento);
    }
}
// Ejercicio2
bool c_ej2_existeclave(Cola c, int clave)
{
    Cola aux = c_crear();
    bool resultado = false;
    TipoElemento ele;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        if (ele->clave == clave)
        {
            resultado = true;
        }
        c_encolar(aux, ele);
    }
    // ENCOLO DE NUEVO
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
    }
    return resultado;
}

Cola c_ej2_colarelemento(Cola c, int posicionordinal)
{
    Cola aux = c_crear();
    Cola resultado = c_crear();
    TipoElemento ele;
    int elemento;
    int i = 1;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        c_encolar(aux, ele);
    }
    // ENCOLO DE NUEVO
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
        c_encolar(resultado, ele);
        i++;
        if (i == posicionordinal)
        {
            ele = te_crear(elemento);
            c_encolar(resultado, ele); // ENCOLO EL ELEMENTO EN LA POS;
        }
    }
    return resultado;
}

Cola c_ej2_sacarelemento(Cola c, int clave)
{
    bool resultB = c_ej2_existeclave(c, clave);
    Cola resultado = c_crear();
    Cola aux = c_crear();
    TipoElemento ele;
    if (!resultB)
    {
        return c;
    }
    else
    {
        while (!c_es_vacia(c))
        {
            ele = c_desencolar(c);
            c_encolar(aux, ele);
        }

        // Reencolo, para en el resultado poder quitar el elemento
        while (!c_es_vacia(aux))
        {
            ele = c_desencolar(aux);
            c_encolar(c, ele);
            // Siempre que el elemento sea distinto a la clave, lo encolamos en el resultado;
            if (ele->clave != clave)
            {
                c_encolar(resultado, ele);
            }
        }
        return resultado;
    }
}

int c_ej2_contarelementos(Cola c)
{
    TipoElemento ele;
    Cola aux = c_crear();
    int resultado = 0;
    if (c_es_vacia(c))
    {
        return 0;
    }
    else
    {
        TipoElemento ele = c_desencolar(c);
        int resultado = 1 + c_ej2_contarelementos(c);
        c_encolar(c, ele);
        return resultado;
    }
}

Cola c_ej2_copiar(Cola c)
{
    Cola resultado = c_crear();
    Cola aux = c_crear();
    TipoElemento ele;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        c_encolar(resultado, ele);
        c_encolar(aux, ele);
    }
    // ENCOLO EN LA ORIGINAL
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
    }
    return resultado;
}

Cola c_ej2_invertir(Cola c)
{
    Cola resultado = c_crear();
    Pila invertir = p_crear();
    Cola aux = c_crear();
    TipoElemento ele;
    while (!c_es_vacia(c))
    {
        ele = c_desencolar(c);
        p_apilar(invertir, ele);
        c_encolar(aux, ele);
    }
    // Invierto
    while (!p_es_vacia(invertir))
    {
        ele = p_desapilar(invertir);
        c_encolar(resultado, ele);
    }
    // Reencolo en cola original
    while (!c_es_vacia(aux))
    {
        ele = c_desencolar(aux);
        c_encolar(c, ele);
    }
    return resultado;
}

// Ejercicio3
// complejidad O(n+m)
bool c_ej3_iguales(Cola c1, Cola c2)
{
    Cola aux = c_crear();
    bool resultado = true;
    TipoElemento ele1, ele2;
    if (c_ej2_contarelementos(c1) != c_ej2_contarelementos(c2)) // O(n+m)
    {
        return false;
    }
    while (!c_es_vacia(c1)) // O(n)
    {
        ele1 = c_desencolar(c1);
        ele2 = c_desencolar(c2);
        if (ele1->clave != ele2->clave)
        {
            resultado = false;
        }
        c_encolar(aux, ele1);
        c_encolar(aux, ele2);
    }
    // ENCOLO NUEVAMENTE EN LAS COLAS
    while (!c_es_vacia(aux))
    {
        ele1 = c_desencolar(aux);
        ele2 = c_desencolar(aux);
        c_encolar(c1, ele1);
        c_encolar(c2, ele2);
    }
    return resultado;
}

// Ejercicio 4

// Complejidad: O(n)
Cola c_ej4_colanorepetidos(Cola c)
{
    Cola aux = c_crear();
    Cola repetidos = c_crear();
    Cola resultado = c_crear();
    while (!c_es_vacia(c))
    {
        TipoElemento ele = c_desencolar(c);
        c_encolar(aux, ele);
    }
    while (!c_es_vacia(aux))
    {
        TipoElemento ele = c_desencolar(aux);
        c_encolar(c, ele);
        if (c_ej2_existeclave(aux, ele->clave))
        {
            c_encolar(repetidos, ele);
        }
        else if (!c_ej2_existeclave(repetidos, ele->clave))
        {
            c_encolar(resultado, ele);
        }
    }

    return resultado;
}

// Ejercicio 5
// Complejidad: O(n^2)
int c_ej5_divisortotal(Cola c, bool *fuetotal)
{
    Cola aux = c_crear();
    Cola aux2 = c_crear();
    int minimo = 9999;
    int longitud = 0;
    int cantidadDivisores = 0;
    while (!c_es_vacia(c))
    {
        TipoElemento ele = c_desencolar(c);
        if (ele->clave < 2)
        {
            printf("La cola no puede tener elementos menores a 2\n");
            return 0;
        }
        if (ele->clave < minimo)
        {
            minimo = ele->clave;
        }
        longitud++;
        c_encolar(aux, ele);
    }
    while (!c_es_vacia(aux))
    {
        TipoElemento ele = c_desencolar(aux);
        if (ele->clave % minimo == 0)
        {
            cantidadDivisores++;
        }
        c_encolar(c, ele);
        c_encolar(aux2, ele);
    }
    if (cantidadDivisores == longitud)
    {
        *fuetotal = true;
        return minimo;
    }
    else 
    {
        *fuetotal = false;
        while (!c_es_vacia(aux2))
        {
            cantidadDivisores = 0;
            TipoElemento divisor = c_desencolar(aux2);
            while (!c_es_vacia(c))
            {
                TipoElemento ele = c_desencolar(c);
                if (ele->clave % divisor->clave == 0)
                {
                    cantidadDivisores++;
                }
                c_encolar(aux, ele);
            }
            while (!c_es_vacia(aux))
            {
                TipoElemento ele = c_desencolar(aux);
                c_encolar(c, ele);
            }
            if (cantidadDivisores > longitud / 2)
            {
                return divisor->clave;
            }
        }
    }

    return 0;
}

// Ejercicio 6
// complejidad O(n^2)
Lista c_ej6_comunesapilaycola(Pila p, Cola c)
{
    Lista listaResultado = l_crear();
    Cola c_aux = c_crear();
    Pila p_aux = p_crear();
    int pos_cola = 0, pos_pila = 0;
    TipoElemento elem_cola, elem_pila;
    while (!p_es_vacia(p)) // complejidad O(n^2)
    {
        elem_pila = p_desapilar(p);
        pos_pila++;
        p_apilar(p_aux, elem_pila);

        while (!c_es_vacia(c)) // O(m)
        {
            elem_cola = c_desencolar(c);
            pos_cola++;
            c_encolar(c_aux, elem_cola);
            if (elem_pila->clave == elem_cola->clave) // O(1)
            {
                TipoElemento ele_resultado = te_crear(elem_pila->clave);
                ele_resultado->valor = (char *)malloc(4 * sizeof(char));
                sprintf(ele_resultado->valor, "%d:%d", pos_cola, pos_pila);
                l_agregar(listaResultado, ele_resultado);
            }
        }
        // REENCOLA
        while (!c_es_vacia(c_aux)) // O(m)
        {
            elem_cola = c_desencolar(c_aux);
            c_encolar(c, elem_cola);
        }
        pos_cola = 0;
    }
    while (!p_es_vacia(p_aux)) // O(n)
    {
        elem_pila = p_desapilar(p_aux);
        p_apilar(p, elem_pila);
    }
    return listaResultado;
}

// Ejercicio 7
// Complejidad 0(n)
TipoElemento c_ej7_atenderclientesAux(TipoElemento ele, int tiempoatencion, int numeroDeCola, int pos)
{
    ele->clave -= tiempoatencion;
    TipoElemento eleCreado = ele;
    if (ele->clave < tiempoatencion)
    {
        eleCreado = te_crear(numeroDeCola);
        eleCreado->valor = (char *)malloc(20 * sizeof(char));
        sprintf(eleCreado->valor, "Cliente:%d Cola:%d", pos, numeroDeCola);
    }
    return eleCreado;
}

Cola c_ej7_atenderclientes(Cola c1, Cola c2, Cola c3, int tiempoatencion)
{
    Cola resu = c_crear();
    TipoElemento ele;
    int pos1 = 1, pos2 = 1, pos3 = 1;
    bool flag = true;
    while (flag)
    {
        if (!c_es_vacia(c1))
        {
            ele = c_ej7_atenderclientesAux(c_recuperar(c1), tiempoatencion, 1, pos1);
            if (ele->clave < tiempoatencion)
            {
                printf("%s\n", (char *)ele->valor);
                c_encolar(resu, ele);
                ele = c_desencolar(c1);
                pos1++;
            }
        }

        if (!c_es_vacia(c2))
        {
            ele = c_ej7_atenderclientesAux(c_recuperar(c2), tiempoatencion, 2, pos2);
            if (ele->clave < tiempoatencion)
            {
                printf("%s\n", (char *)ele->valor);
                c_encolar(resu, ele);
                ele = c_desencolar(c2);
                pos2++;
            }
        }

        if (!c_es_vacia(c3))
        {
            ele = c_ej7_atenderclientesAux(c_recuperar(c3), tiempoatencion, 3, pos3);
            if (ele->clave < tiempoatencion)
            {
                printf("%s\n", (char *)ele->valor);
                c_encolar(resu, ele);
                ele = c_desencolar(c3);
                pos3++;
            }
        }

        if (c_es_vacia(c1) && c_es_vacia(c2) && c_es_vacia(c3))
        {
            flag = false;
        }
    }
    return resu;
}

int main()
{
    // Cola c1 = c_crear();
    // rellenarCola(c1, 4);
    // printf("EJERCICIO EXISTE CLAVE\n");
    // bool resultado1 = c_ej2_existeclave(c1, 3);
    // if (resultado1)
    // {
    //     printf("Existe la clave en la pila\n");
    // }
    // else
    // {
    //     printf("No existe la clave en la pila\n");
    // }

    // Cola c2 = c_ej4_colanorepetidos(c1);
    // printf("Cola 1\n");
    // c_mostrar(c1);
    // printf("Cola de no repetidos\n");
    // c_mostrar(c2);

    // main EJERCICIO 6
    // Pila p1 = p_crear();
    // rellenarPila(p1,5);
    // printf("----------------------\n");
    // Cola c1 = c_crear();
    // rellenarCola(c1,5);
    // Lista resultado = c_ej6_comunesapilaycola(p1,c1);
    // c_mostrar(c1);
    // p_mostrar(p1);
    // printf("La lista resultante es: \n");
    // l_mostrar(resultado);
    // if (resultado->inicio==NULL){
    //     printf("LISTA VACIA (NO hay elementos coincidentes)");
    // }
    // else{
    //     l_mostrar(resultado);
    // }
    // Iterador iteL1 = iterador(resultado);
    // while (hay_siguiente(iteL1))
    //{
    //     TipoElemento eleLis = siguiente(iteL1);
    //     printf("El elemento es %d y sus posiciones son: %s  \n", eleLis->clave, 1;
    // }

    // Ejercicio 5
    // Cola c1 = c_crear();
    // c_encolar(c1, te_crear(30));
    // c_encolar(c1, te_crear(9));
    // c_encolar(c1, te_crear(2));
    // c_encolar(c1, te_crear(3));
    // c_encolar(c1, te_crear(4));
    // c_mostrar(c1);
    // bool fuetotal = false;
    // int resultado = c_ej5_divisortotal(c1, &fuetotal);
    // printf("El divisor es: %d\n", resultado);
    // printf("Fue total? %s\n", fuetotal ? "SI" : "NO");

    // Ejercicio7
    // Cola c1 = c_crear();
    // Cola c2 = c_crear();
    // Cola c3 = c_crear();
    // rellenarCola(c1, 2);
    // printf("-----------\n");
    // rellenarCola(c2, 2);
    // printf("-----------\n");
    // rellenarCola(c3, 2);
    // printf("-----------\n");
    // Cola resu = c_ej7_atenderclientes(c1,c2,c3, 7);
    // printf("-----------\n");
    // c_mostrar(resu);

    return 0;
}

// gcc -o test_tp4 ./tp4/main.c ./libs/colas/colas_arreglos.c ./libs/listas/listas_arreglos.c ./libs/pilas/pilas_arreglos.c ./libs/elementos/tipo_elemento.c && ./test_tp4