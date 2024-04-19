#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TP_2_Listas.h"

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

void printLista(Lista lista)
{
    printf("| ");
    l_mostrar(lista);
    printf("\n");
}

void testPt2(Lista lista1, Lista lista2)
{
    clearScreen();
    while (1)
    {
        printf("\n\n+------------------------------------------------------------------------------------------+\n");
        printf("| Test de Ejercicio 2.:\n");
        printf("| 1. Ver elementos repetidos\n");
        printf("| 2. Ver elementos de la lista 1 que no se repiten en la lista 2\n");
        printf("| 3. Ver elementos de la lista 2 que no se repiten en la lista 1\n");
        printf("| 4. Promedio de la lista 1\n");
        printf("| 5. Promedio de la lista 2\n");
        printf("| 6. Promedio de ambas listas\n");
        printf("| 7. Valor maximo de ambas listas\n");
        printf("| 8. Volver al menu principal\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Ver elementos repetidos:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            printf("| Elementos repetidos: \n");
            printLista(verElementosRepetidos(lista1, lista2));
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 2:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Ver elementos de la lista 1 que no se repiten en la lista 2:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            printf("| Elementos que no se repiten: \n");
            printLista(verElementosQueNoSeRepiten(lista1, lista2));
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 3:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Ver elementos de la lista 2 que no se repiten en la lista 1:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            printf("| Elementos que no se repiten: \n");
            printLista(verElementosQueNoSeRepiten(lista2, lista1));
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 4:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Promedio de la lista 1:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Promedio: %f\n", promedio(lista1));
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 5:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Promedio de la lista 2:\n");
            printf("| Lista 2: \n");
            printLista(lista2);
            printf("| Promedio: %f\n", promedio(lista2));
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 6:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Promedio de ambas listas:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            Resultados res = promedioAmbasListas(lista1, lista2);
            printf("| Promedio de la lista 1: %f\n", res.resultado1);
            printf("| Promedio de la lista 2: %f\n", res.resultado2);
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();

            break;
        case 7:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Valor maximo de ambas listas:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            ResultadoValorMaximo resMax = valorMaximo(lista1, lista2);
            printf("| Posicion: %d\n", resMax.pos);
            printf("| Lista: %d\n", resMax.lista);
            printf("| Valor: %d\n", resMax.valor);
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 8:
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

void testPt3(Lista lista1, Lista lista2)
{
    clearScreen();
    while (1)
    {
        printf("\n\n+------------------------------------------------------------------------------------------+\n");
        printf("| Test de Ejercicio 3.:\n");
        printf("| 1. Multiplo\n");
        printf("| 2. Volver al menu principal\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Multiplo:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            ResultadosMul resultado = multiplo(lista1, lista2);
            if (!resultado.esMultiplo)
            {
                printf("| Las listas no son multiplos\n");
            }
            else
            {
                printf("| Las listas son multiplos\n");
                if (resultado.escalar)
                {
                    printf("| El escalar es: %d\n", resultado.numEscalar);
                }
            }
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 2:
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

void testPt4(Lista lista1, Lista lista2)
{
    clearScreen();
    while (1)
    {
        printf("\n\n+------------------------------------------------------------------------------------------+\n");
        printf("| Test de Ejercicio 4.:\n");
        printf("| 1. Comparar listas\n");
        printf("| 2. Volver al menu principal\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Comparar listas:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            CompararListas(lista1, lista2);
            printf("\n+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 2:
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

void testPt6(Lista lista1, Lista lista2)
{
    clearScreen();
    while (1)
    {
        printf("\n\n+------------------------------------------------------------------------------------------+\n");
        printf("| Test de Ejercicio 6.:\n");
        printf("| 1. Es sublista\n");
        printf("| 2. Volver al menu principal\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Es sublista:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Lista 2: \n");
            printLista(lista2);
            if (esSublista(lista1, lista2))
            {
                printf("| La lista 2 es sublista de la lista 1\n");
            }
            else
            {
                printf("| La lista 2 no es sublista de la lista 1\n");
            }
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 2:
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

void testPt5()
{
    clearScreen();

    int i;
    TipoElemento item;
    Lista list = l_crear();
    Lista respuesta = l_crear();
    double resp;
    double *array_valores;

    while (1)
    {
        printf("\n\n+------------------------------------------------------------------------------------------+\n");
        printf("| Test de Ejercicio 5.:\n");
        printf("| 1. Polinomio\n");
        printf("| 2. Volver al menu principal\n");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("\nIngrese una opcion: ");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:

            hacerPolinomio(list);
            double desde, hasta, intervalo;
            printf("\nIngrese el valor desde: ");
            scanf("%lf", &desde);
            printf("\nIngrese el valor hasta: ");
            scanf("%lf", &hasta);
            printf("\nIngrese el valor del intervalo: ");
            scanf("%lf", &intervalo);

            respuesta = calcularRango(list, desde, hasta, intervalo);
            printf("\n");

            if (respuesta != NULL)
            {
                l_mostrar(respuesta);

                item = l_recuperar(respuesta, 1);

                if (item != NULL && item->valor != NULL)
                {
                    array_valores = item->valor;

                    for (i = 0; i < l_longitud(respuesta); i++)
                    {
                        printf("\nValor de x = %.2f: %.2f", desde + (intervalo * i), array_valores[i]);
                    }
                }
                else
                {
                    printf("\nError al recuperar el item");
                }
            }
            else
            {
                printf("\nError al crear la lista de respuesta");
            }

            waitForKey();
            break;
        case 2:
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

// Utilidades
Lista rellenarLista(int elementos)
{
    Lista l = l_crear();
    TipoElemento x;
    bool blAg = true;
    for (int i = 0; i < elementos; i++)
    {
        int numero_aleatorio;
        printf("\nIngrese el numero a agregar en la lista: ");
        scanf("%i", &numero_aleatorio);
        x = te_crear(numero_aleatorio);
        blAg = blAg && l_agregar(l, x);
    }
    if (!blAg)
    {
        l = l_crear();
    }
    return l;
}

int main()
{
    clearScreen();
    printf("+------------------------------------------------------------------------------------------+\n");
    printf("| Para poder realizar los test de los ejericicos, primero tendrás que rellenar dos listas. |\n");
    printf("| Ya que la mayoría de los ejercicios requieren de dos listas.                             |\n");
    printf("+------------------------------------------------------------------------------------------+\n");

    Lista lista1;
    Lista lista2;

    printf("\n| ¿Desea rellenar las listas automaticamente? (s/n): ");
    while (1)
    {
        char opcion;
        scanf(" %c", &opcion);
        if (opcion == 's')
        {
            lista1 = l_crear();
            lista2 = l_crear();

            printf("\nIngresa cantidad de elementos para la lista 1: ");
            int cantidad_auto;
            scanf("%d", &cantidad_auto);
            for (int i = 0; i < cantidad_auto; i++)
            {
                int random = rand() % 1000 + 1;
                printf("%d\n", random);
                l_agregar(lista1, te_crear(random));
            }

            printf("\nIngresa cantidad de elementos para la lista 2: ");
            int cantidad_auto2;
            scanf("%d", &cantidad_auto2);
            for (int i = 0; i < cantidad_auto2; i++)
            {
                int random = rand() % 100 + 1;
                printf("%d\n", random);
                l_agregar(lista2, te_crear(random));
            }

            break;
        }
        else if (opcion == 'n')
        {
            printf("\nIngresa cantidad de elementos para la lista 1: ");
            int cantidad;
            scanf("%d", &cantidad);
            lista1 = rellenarLista(cantidad);
            printf("\nIngresa cantidad de elementos para la lista 2: ");
            int cantidad2;
            scanf("%d", &cantidad2);
            lista2 = rellenarLista(cantidad2);

            break;
        }
        else
        {
            printf("| Opcion no valida, intente nuevamente: ");
        }
    }

    printf("\n+------------------------------------------------------------------------------------------+\n");
    printf("| Listas rellenadas:                                                                       |\n");
    printf("+------------------------------------------------------------------------------------------+\n");
    printf("\n| Lista 1: ");
    printLista(lista1);
    printf("| Lista 2: ");
    printLista(lista2);
    printf("+------------------------------------------------------------------------------------------+\n");

    printf("+------------------------------------------------------------------------------------------+\n");
    printf("| Ahora que ya tenes las listas rellenadas, podes realizar los test de los ejercicios.    |\n");
    printf("+------------------------------------------------------------------------------------------+\n");

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
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            testPt2(lista1, lista2);
            break;
        case 2:
            testPt3(lista1, lista2);
            break;
        case 3:
            testPt4(lista1, lista2);
            break;
        case 4:
            testPt5();
            break;
        case 5:
            testPt6(lista1, lista2);
            break;
        case 6:
            return 0;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }

    return 0;
}

// compile command: gcc -o output ./main.c ./listas_arreglos.c ./tipo_elemento.c ./p2.c ./p3.c ./p4.c ./p6.c && ./output.exe