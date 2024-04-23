#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../libs/pilas/pilas.h"
#include "./TP_3_Pilas.h"

// Funciones auxiliares

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

void printPila(Pila pila)
{
    printf("| ");
    p_mostrar(pila);
    printf("\n");
}

Pila rellenarPila(int cantidad)
{
    Pila pila = p_crear();
    for (int i = 0; i < cantidad; i++)
    {
        int valor;
        printf("| Ingresa el valor para el elemento %d: ", i + 1);
        while (scanf("%d", &valor) != 1)
        {
            printf("\nError: Ingresa un número válido para el valor: ");
            while (getchar() != '\n')
            {
                // clear input buffer
            }
        }

        p_apilar(pila, te_crear(valor));
    }

    return pila;
}

Pila crearPila()
{
    Pila pila;

    printf("\n| ¿Desea rellenar la pila automaticamente? (s/n): ");
    while (1)
    {
        char opcion;
        scanf(" %c", &opcion);
        if (opcion == 's')
        {
            pila = p_crear();

            printf("\nIngresa cantidad de elementos para la Pila: ");
            int cantidad_auto;
            while (scanf("%d", &cantidad_auto) != 1 || cantidad_auto > 10)
            {
                printf("\nError: Ingresa un número válido para la cantidad de elementos: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }

            for (int i = 0; i < cantidad_auto; i++)
            {
                int random = rand() % 1000 + 1;
                printf("%d\n", random);
                p_apilar(pila, te_crear(random));
            }

            break;
        }
        else if (opcion == 'n')
        {
            printf("\nIngresa cantidad de elementos para la Pila: ");
            int cantidad;
            while (scanf("%d", &cantidad) != 1 || cantidad > 10)
            {
                printf("\nError: Ingresa un número válido para la cantidad de elementos: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }

            pila = p_crear();
            pila = rellenarPila(cantidad);

            break;
        }
        else
        {
            printf("| Opcion no valida, intente nuevamente: ");
        }
    }

    return pila;
}

// void verComplejidades()
// {
//     printf("\t\t Complejidad de los ejercicios dados\n");
//     printf("------------------------------------------\n");
//     printf("\tComplejidad ejercicio2: \n");
//     printf("\t\t - Existe clave : Lineal - O(n))\n");
//     printf("\t\t - Colocar elemento : Lineal - O(n))\n");
//     printf("\t\t - Eliminar clave : Lineal - O(n))\n");
//     printf("\t\t - Duplicar pila : Lineal - O(n))\n");
//     printf("\t\t - Intercambiar Posiciones: Lineal - O(n))\n");
//     printf("\t\t - Cantidad elementos : Lineal - O(n))\n");
//     printf("------------------------------------------\n");
//     printf("\tComplejidad ejercicio3: \n");
//     printf("\t\t - Iguales : Lineal - O(n))\n");
//     printf("------------------------------------------\n");
//     printf("\tComplejidad ejercicio4: \n");
//     printf("\t\t - Cambiar base : Logaritmico - O(log(n))\n");
//     printf("------------------------------------------\n");
//     printf("\tComplejidad ejercicio5: \n");
//     printf("\t\t - Invertir : Lineal - O(n))\n");
//     printf("------------------------------------------\n");
//     printf("\tComplejidad ejercicio6: \n");
//     printf("\t\t - Eliminar Clave : Lineal - O(n))\n");
//     printf("\t\t - Eliminar ClaveRecursiva : Lineal - O(n))\n");
//     printf("------------------------------------------\n");
//     printf("\tComplejidad ejercicio7: \n");
//     printf("\t\t - Elementos comunes: Cuadratica - O(n^2)\n");
//     printf("------------------------------------------\n");
//     printf("\tComplejidad ejercicio8: \n");
//     printf("\t\t - Sacar repetidos: Cuadratica - O(n^2)\n");
// }
// // Ejercicio2
// // complejidad O(n)
bool p_ej2_existeclave(Pila p, int clave)
{
    bool resultado = false;
    Pila aux = p_crear();
    TipoElemento ele;
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        if (ele->clave == clave)
        {
            resultado = true;
        }
        p_apilar(aux, ele);
    }

    // RECOMPONGO LA PILA INGRESADA
    while (!p_es_vacia(aux))
    {

        ele = p_desapilar(aux);
        p_apilar(p, ele);
    }

    return resultado;
}

// complejidad O(n)
Pila p_ej2_colocarelemento(Pila p, int posicionordinal)
{
    Pila aux = p_crear();
    Pila resultado = p_crear();
    TipoElemento ele;
    int i = 1, elemento;
    // Desapilo
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
    }
    // SOLICITO EL ELEMENTO A AGREGAR EN LA PILA
    printf("Ingrese el elemento que desea agregar: ");
    while (scanf("%d", &elemento) != 1)
    {
        printf("\nError: Ingresa un número válido para la opción: ");
        while (getchar() != '\n')
        {
            // clear input buffer
        }
    }

    // Reapilo, para en el resultado poder agregar el elemento
    while (!p_es_vacia(aux))
    {
        ele = p_desapilar(aux);
        p_apilar(p, ele);
        p_apilar(resultado, ele);
        i++;
        if (i == posicionordinal)
        {
            ele = te_crear(elemento);
            p_apilar(resultado, ele); // Agrego el elemento al resultado;
        }
    }

    return resultado;
}

// complejidad O(n)
Pila p_ej2_eliminarclave(Pila p, int clave)
{
    bool resulBusqueda = p_ej2_existeclave(p, clave);
    Pila resultado = p_crear();
    Pila aux = p_crear();
    TipoElemento ele;
    if (!resulBusqueda)
    {
        return p;
    }
    else
    {
        while (!p_es_vacia(p))
        {
            ele = p_desapilar(p);
            p_apilar(aux, ele);
        }

        // Reapilo, para en el resultado poder quitar el elemento
        bool flag = true; // flag para que sea solo en la primer ocurrencia;
        while (!p_es_vacia(aux))
        {
            ele = p_desapilar(aux);
            p_apilar(p, ele); // Linea para conservar pila original
            // Siempre que el elemento sea distinto a la clave, lo apilamos en el resultado;
            if (ele->clave == clave && flag)
            {
                flag = false;
            }
            else
            {
                p_apilar(resultado, ele);
            }
        }
        return resultado;
    }
}

// complejidad O(n)
Pila p_ej2_duplicar(Pila p)
{
    Pila resultado = p_crear();
    Pila aux = p_crear();
    TipoElemento ele;
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
    }

    while (!p_es_vacia(aux))
    {

        ele = p_desapilar(aux);
        p_apilar(p, ele);
        p_apilar(resultado, ele);
        p_apilar(resultado, ele);
    }

    return resultado;
}

// complejidad O(n)
Pila p_ej2_intercambiarposiciones(Pila p, int pos1, int pos2)
{
    Pila aux = p_crear();
    Pila resultado = p_crear();
    TipoElemento ele;
    TipoElemento ele1;
    TipoElemento ele2;
    int i = 1;
    while (!p_es_vacia(p))
    {
        ele = p_desapilar(p);
        p_apilar(aux, ele);
        if (i == pos1)
        {
            ele1 = ele;
        }
        else if (i == pos2)
        {
            ele2 = ele;
        }
        i++;
    }
    while (!p_es_vacia(aux))
    {
        ele = p_desapilar(aux);
        p_apilar(p, ele);
        if (ele->clave == ele2->clave)
        {
            p_apilar(resultado, ele1);
        }
        else if (ele->clave == ele1->clave)
        {
            p_apilar(resultado, ele2);
        }
        else
        {
            p_apilar(resultado, ele);
        }
    }

    return resultado;
}

// O(n)
int p_ej2_cantidadelementos(Pila p)
{
    if (p_es_vacia(p))
    {
        return 0;
    }
    else
    {
        TipoElemento ele = p_desapilar(p);
        int count = 1 + p_ej2_cantidadelementos(p);
        p_apilar(p, ele);
        return count;
    }
}

// // Ejercicio 3
// // complejidad: O(n)
bool p_ej3_iguales(Pila p1, Pila p2)
{
    Pila aux = p_crear();
    TipoElemento ele1, ele2;
    bool resultado = true;
    while (!p_es_vacia(p1) && !p_es_vacia(p2) && resultado)
    {
        ele1 = p_desapilar(p1);
        ele2 = p_desapilar(p2);
        p_apilar(aux, ele1);
        p_apilar(aux, ele2);
        if (ele1->clave != ele2->clave)
        {
            resultado = false;
        }
    }
    // Hago otro ciclo para reapilar lo que saque de las pilas originales.
    while (!p_es_vacia(aux))
    {
        ele1 = p_desapilar(aux);
        ele2 = p_desapilar(aux);
        p_apilar(p2, ele1);
        p_apilar(p1, ele2);
    }

    return resultado;
}

// // ejercicio 4
// // complejidad: O(log(n))
// char *p_ej4_cambiarbase(int numero, int base)
// {
//     // validacion de base
//     if (base < 2 || base > 16)
//     {
//         printf("La base debe estar entre 2 y 16.\n");
//         exit(EXIT_FAILURE);
//     }
//     // Variable para almacenar el signo
//     char signo = (numero < 0) ? '-' : ' ';

//     // Trabajar con el valor absoluto del número
//     numero = abs(numero);

//     int resto;
//     TipoElemento item;
//     Pila pililla;
//     pililla = p_crear();

//     while (numero > 0)
//     {
//         resto = numero % base;
//         item = te_crear(resto);
//         p_apilar(pililla, item);
//         numero /= base;
//     }

//     printf("\n");
//     p_mostrar(pililla);

//     char *numero_cambiado = malloc(sizeof(char) * p_ej2_cantidadelementos(pililla) + 1);

//     int i = 0;
//     if (signo == '-')
//     {
//         numero_cambiado[i++] = signo;
//     }
//     while (!p_es_vacia(pililla))
//     {
//         item = p_desapilar(pililla);
//         if (item->clave < 10)
//         {
//             numero_cambiado[i++] = item->clave + '0'; // Convertir el dígito a su representación ASCII
//         }
//         else
//         {
//             numero_cambiado[i++] = item->clave - 10 + 'A'; // Convertir el dígito a su representación ASCII en hexadecimal
//         }
//     }

//     return numero_cambiado;
// }

// // Ejercicio 5
// // complejidad: O(n)
// Pila p_ej5_invertir(Pila p)
// {
//     Pila aux = p_crear();
//     Pila invertida = p_crear();
//     TipoElemento ele;
//     while (!p_es_vacia(p))
//     {
//         ele = p_desapilar(p);
//         p_apilar(aux, ele);
//         p_apilar(invertida, ele);
//     }
//     // REAPILO PARA NO PERDER ORIGINAL
//     while (!p_es_vacia(aux))
//     {
//         ele = p_desapilar(aux);
//         p_apilar(p, ele);
//     }
//     return invertida;
// }

// // Ejercicio 6
// // complejidad solucion iterativa: O(n)
// Pila p_ej6_eliminarclave(Pila p, int clave)
// {
//     bool resulBusqueda = p_ej2_existeclave(p, clave);
//     Pila resultado = p_crear();
//     Pila aux = p_crear();
//     TipoElemento ele;
//     if (!resulBusqueda)
//     {
//         return p;
//     }
//     else
//     {
//         while (!p_es_vacia(p))
//         {
//             ele = p_desapilar(p);
//             p_apilar(aux, ele);
//         }

//         // Reapilo, para en el resultado poder quitar el elemento
//         while (!p_es_vacia(aux))
//         {
//             ele = p_desapilar(aux);
//             p_apilar(p, ele); // Linea para conservar pila original
//             // Siempre que el elemento sea distinto a la clave, lo apilamos en el resultado;
//             if (ele->clave != clave)
//             {
//                 p_apilar(resultado, ele);
//             }
//         }
//         return resultado;
//     }
// }

// // complejidad solucion recursiva: O(n)
// Pila p_ej6_eliminarclave_recursiva(Pila p, int clave)
// {
//     if (p_es_vacia(p))
//     {
//         return p;
//     }
//     else
//     {
//         TipoElemento ele = p_desapilar(p);
//         Pila resultado = p_ej6_eliminarclave_recursiva(p, clave);
//         if (ele->clave != clave)
//         {
//             p_apilar(resultado, ele);
//         }
//         return resultado;
//     }
// }

// // Ejercicio7
// // complejidad: O(n^2)
// Pila p_ej7_elementoscomunes(Pila p1, Pila p2)
// {
//     Pila aux1 = p_crear();
//     Pila aux2 = p_crear();
//     Pila resultado = p_crear();
//     TipoElemento ele1;
//     TipoElemento ele2;

//     while (!p_es_vacia(p1))
//     {
//         ele1 = p_desapilar(p1);
//         p_apilar(aux1, ele1);
//         bool flag = true;
//         while (!p_es_vacia(p2) && flag)
//         {
//             ele2 = p_desapilar(p2);
//             p_apilar(aux2, ele2);
//             if (ele1->clave == ele2->clave)
//             {
//                 p_apilar(resultado, ele1);
//             }
//         }
//         // APILO LO QUE DESAPILE, PARA QUE EL SIGUIENTE ELEMENTO PUEDA COMPARARSE
//         while (!p_es_vacia(aux2))
//         {
//             ele2 = p_desapilar(aux2);
//             p_apilar(p2, ele2);
//         }
//     }
//     // APILO NUEVAMENTE EN P1 PARA NO PERDERLA.
//     while (p_es_vacia(aux1))
//     {
//         ele1 = p_desapilar(aux1);
//         p_apilar(p1, ele1);
//     }

//     return resultado;
// }

// // ejercicio 8
// //  complejidad: O(n^2)
// Pila p_ej8_sacarrepetidos(Pila p)
// {
//     Pila resultado = p_crear();
//     Pila aux = p_crear();
//     Pila p_original = p_crear(); // Pila original
//     while (!p_es_vacia(p))
//     {
//         TipoElemento ele = p_desapilar(p);
//         p_apilar(aux, ele);        // guardar elemento en pila auxiliar
//         p_apilar(p_original, ele); // guardar elemento en una copia dee la pila original
//     }
//     while (!p_es_vacia(aux))
//     {
//         // desapilo un elemento de la pila auxiliar
//         TipoElemento ele = p_desapilar(aux);
//         int cantidad = 1;
//         // creo una segunda pila auxiliar con los valores de la pila auxiliar
//         Pila aux2 = p_crear();
//         while (!p_es_vacia(aux))
//         {
//             TipoElemento auxEle = p_desapilar(aux);
//             p_apilar(aux2, auxEle);
//         }
//         // recorro la pila auxiliar 2 para contar la cantidad de veces que se repite el elemento, y elimino los elementos repetidos de la pila auxiliar
//         while (!p_es_vacia(aux2))
//         {
//             TipoElemento auxEle = p_desapilar(aux2);
//             if (auxEle->clave == ele->clave)
//             {
//                 cantidad++;
//             }
//             else
//             {
//                 p_apilar(aux, auxEle);
//             }
//         }
//         // creo un nuevo elemento con la cantidad de veces que se repite el elemento
//         TipoElemento cuenta = te_crear_con_valor(ele->clave, cantidad);
//         // apilo el elemento en la pila resultado
//         p_apilar(resultado, cuenta);
//     }

//     // Restaurar pila original
//     while (!p_es_vacia(p_original))
//     {
//         TipoElemento ele = p_desapilar(p_original);
//         p_apilar(p, ele);
//     }

//     return resultado;
// }

void testPt2()
{
    clearScreen();
    Pila pila = crearPila();
    Pila pila_duplicada;
    int cantidad_elementos;

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("\n| Pila: ");
        printPila(pila);
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Existe clave\n");
        printf("| 2. Colocar elemento\n");
        printf("| 3. Eliminar clave\n");
        printf("| 4. Duplicar pila\n");
        printf("| 5. Intercambiar posiciones\n");
        printf("| 6. Cantidad elementos\n");
        printf("| 7. Volver al menu principal\n");
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
            printf("\nIngrese la clave a buscar: ");
            int clave;
            while (scanf("%d", &clave) != 1)
            {
                printf("\nError: Ingresa un número válido para la clave: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }
            bool resultado1 = p_ej2_existeclave(pila, clave);
            if (resultado1)
            {
                printf("La clave %d existe en la pila\n", clave);
            }
            else
            {
                printf("La clave %d no existe en la pila\n", clave);
            }

            waitForKey();
            break;
        case 2:
            printf("\nIngrese la posicion ordinal donde desea colocar el elemento: ");
            int posicion;
            while (scanf("%d", &posicion) != 1)
            {
                printf("\nError: Ingresa un número válido para la posición: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }
            Pila resultado2 = p_ej2_colocarelemento(pila, posicion);
            printf("\n+------------------------------------------------------------------------------------------+\n");
            printf("| Pila original:\n");
            printPila(pila);
            printf("| Pila con elemento colocado:\n");
            printPila(resultado2);
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 3:
            printf("\nIngrese la clave a eliminar: ");
            int claveEliminar;
            while (scanf("%d", &claveEliminar) != 1)
            {
                printf("\nError: Ingresa un número válido para la clave: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }
            Pila pila_eliminar_clave = p_ej2_eliminarclave(pila, claveEliminar);
            printf("\n+------------------------------------------------------------------------------------------+\n");
            printf("| Pila original:\n");
            printPila(pila);
            printf("| Pila sin clave:\n");
            printPila(pila_eliminar_clave);
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 4:
            pila_duplicada = p_ej2_duplicar(pila);
            printf("\n+------------------------------------------------------------------------------------------+\n");
            printf("| Pila original:\n");
            printPila(pila);
            printf("| Pila duplicada:\n");
            printPila(pila_duplicada);
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();

            free(pila_duplicada);

            break;
        case 5:
            printf("\nIngrese la primera posicion a intercambiar: ");
            int pos1;
            while (scanf("%d", &pos1) != 1)
            {
                printf("\nError: Ingresa un número válido para la posición: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }
            printf("\nIngrese la segunda posicion a intercambiar: ");
            int pos2;
            while (scanf("%d", &pos2) != 1)
            {
                printf("\nError: Ingresa un número válido para la posición: ");
                while (getchar() != '\n')
                {
                    // clear input buffer
                }
            }
            Pila resultado5 = p_ej2_intercambiarposiciones(pila, pos1, pos2);
            printf("\n+------------------------------------------------------------------------------------------+\n");
            printf("| Pila original:\n");
            printPila(pila);
            printf("| Pila con posiciones intercambiadas:\n");
            printPila(resultado5);
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 6:
            cantidad_elementos = p_ej2_cantidadelementos(pila);
            printf("\n+------------------------------------------------------------------------------------------+\n");
            printf("| Pila:\n");
            printPila(pila);
            printf("| La pila tiene %d elementos\n", cantidad_elementos);
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 7:
            clearScreen();
            return;
        default:
            printf("\nOpcion no valida");

            waitForKey();
            break;
        }
    }
}

void testPt3()
{
    clearScreen();
    Pila pila1 = crearPila();
    Pila pila2 = crearPila();

    bool resultado;

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("\n| Pila 1: ");
        printPila(pila1);
        printf("\n| Pila 2: ");
        printPila(pila2);
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Verificar si las pilas son iguales\n");
        printf("| 2. Volver al menu principal\n");
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
            resultado = p_ej3_iguales(pila1, pila2);
            if (resultado)
            {
                printf("Las pilas son iguales\n");
            }
            else
            {
                printf("Las pilas son diferentes\n");
            }

            waitForKey();
            break;
        case 2:
            clearScreen();
            return;
        default:
            printf("\nOpcion no valida");

            waitForKey();
            break;
        }
    }
}

int main()
{
    clearScreen();
    printf("Archivo compilado exitosamente\n");
    printf("Para ejecutar los ejercicios, descomentar las lineas de codigo en el main\n");
    printf("Esto es unicamente para comprobar que la compilacion fue exitosa\n");

    while (1)
    {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Probar funciones del punto 2\n");
        printf("| 2. Probar funciones del punto 3\n");
        printf("| 3. Probar funciones del punto 4\n");
        printf("| 4. Probar funciones del punto 5\n");
        printf("| 5. Probar funciones del punto 6\n");
        printf("| 6. Salir\n");
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
            testPt2();
            break;
        case 2:
            testPt3();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            return 0;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }

    // Pila pila = p_crear();
    // Pila pila2 = p_crear();
    // rellenarPila(pila, 4);
    // printf("----------------------\n");
    // rellenarPila(pila2, 4);
    // printf("\t------------------------------\n");
    // printf("\t ----- PILA PRINCIPAL ----\n");
    // p_mostrar(pila);
    // printf("\t------------------------------\n");
    // printf("EJERCICIO INTERCAMBIAR POSICIONES\n");
    // Pila resultado1 = p_ej2_intercambiarposiciones(pila, 2, 4);
    // p_mostrar(resultado1);
    // printf("------------------------------\n");
    // printf("EJERCICIO EXISTE CLAVE\n");
    // bool resultado2 = p_ej2_existeclave(pila, 3);
    // if (resultado2)
    // {
    //     printf("Existe la clave en la pila\n");
    // } else {printf("No existe la clave en la pila\n");}
    // printf("------------------------------\n");
    // printf("EJERCICIO COLOCAR CLAVE\n");
    // Pila resultado3 =  p_ej2_colocarelemento(pila, 3);
    // p_mostrar(resultado3);
    // printf("------------------------------\n");
    // printf("EJERCICIO ELIMINAR CLAVE\n");
    // Pila resultado4 = p_ej2_eliminarclave(pila, 3);
    // p_mostrar(resultado4);
    // printf("------------------------------\n");
    // printf("EJERCICIO DUPLICAR PILA\n");
    // Pila resultado5 = p_ej2_duplicar(pila);
    // p_mostrar(resultado5);
    // printf("------------------------------\n");
    // printf("EJERCICIO CANTIDAD ELEMENTOS\n");
    // int resultado6 = p_ej2_cantidadelementos(pila);
    // printf("La pila tiene %d elementos\n", resultado6);

    // printf("------------------------------\n");
    // printf("EJERCICIO 3 - LISTAS IGUALES\n");
    // bool resultadoPt3 = p_ej3_iguales(pila, pila2);
    // if (resultadoPt3)
    // {
    //     printf("LAS LISTAS SON IGUALES\n");
    // } else {printf("LAS LISTAS SON DIFERENTES\n");}
    // printf("\t\t- Como quedan las pilas originales despues del retorno -\n");
    // printf("\t\t\t PILA 1\n");
    // p_mostrar(pila);
    // printf("\t\t\t PILA 2\n");
    // p_mostrar(pila2);
    // printf("------------------------------\n");
    // printf("EJERCICIO 5 - INVERTIR\n");
    // Pila resultadoPt5 = p_ej5_invertir(pila);
    // p_mostrar(resultadoPt5);
    // printf("\t\t- Como queda pila oriignal despues del retorno -\n");
    // p_mostrar(pila);
    // printf("------------------------------\n");
    // printf("EJERCICIO 7 - ELEMENTOS COMUNES\n");
    // Pila resultadoPt7 = p_ej7_elementoscomunes(pila,pila2);
    // p_mostrar(resultadoPt7);

    // probar ejercicio 8
    // Pila pila = p_crear();
    // rellenarPila(pila, 4);
    // Pila resultado = p_ej8_sacarrepetidos(pila);
    // p_mostrar(pila);
    // p_mostrar(resultado);
    // while (!p_es_vacia(resultado))
    // {
    //     TipoElemento ele = p_desapilar(resultado);
    //     printf("Clave: %d, Cantidad: %d\n", ele->clave, ele->valor);
    // }

    // return 0;
}