#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listas.h"
#include "ejercicios.h"

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
    while (1)
    {
        printf("\n\n+------------------------------------------------------------------------------------------+\n");
        printf("| Test de Ejercicio 2.:\n");
        printf("| 1. Ver elementos repetidos\n");
        printf("| 2. Ver elementos que no se repiten\n");
        printf("| 3. Promedio de la lista 1\n");
        printf("| 4. Promedio de la lista 2\n");
        printf("| 5. Promedio de ambas listas\n");
        printf("| 6. Valor maximo de ambas listas\n");
        printf("| 7. Volver al menu principal\n");
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
            printf("| Ver elementos que no se repiten:\n");
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
            printf("| Promedio de la lista 1:\n");
            printf("| Lista 1: \n");
            printLista(lista1);
            printf("| Promedio: %f\n", promedio(lista1));
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 4:
            printf("+------------------------------------------------------------------------------------------+\n");
            printf("| Promedio de la lista 2:\n");
            printf("| Lista 2: \n");
            printLista(lista2);
            printf("| Promedio: %f\n", promedio(lista2));
            printf("+------------------------------------------------------------------------------------------+\n");

            waitForKey();
            break;
        case 5:
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
        case 6:
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
        case 7:
            return;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }
}

void testPt3(Lista lista1, Lista lista2)
{
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

int main()
{
    printf("+------------------------------------------------------------------------------------------+\n");
    printf("| Para poder realizar los test de los ejericicos, primero tendrás que rellenar dos listas. |\n");
    printf("| Ya que la mayoría de los ejercicios requieren de dos listas.                             |\n");
    printf("+------------------------------------------------------------------------------------------+\n");

    Lista lista1;
    Lista lista2;

    printf("\nIngresa cantidad de elementos para la lista 1: ");
    int cantidad;
    scanf("%d", &cantidad);
    lista1 = rellenarLista(cantidad);
    printf("\nIngresa cantidad de elementos para la lista 2: ");
    int cantidad2;
    scanf("%d", &cantidad2);
    lista2 = rellenarLista(cantidad2);

    printf("\n+------------------------------------------------------------------------------------------+\n");
    printf("| Listas rellenadas:                                                                       |\n");
    printf("+------------------------------------------------------------------------------------------+\n");
    printf("| Lista 1: ");
    printLista(lista1);
    printf("| Lista 2: ");
    printLista(lista2);
    printf("+------------------------------------------------------------------------------------------+\n");

    printf("\n+------------------------------------------------------------------------------------------+\n");
    printf("| Ahora que ya tenes las listas rellenadas, podes realizar los test de los ejercicios.    |\n");
    printf("+------------------------------------------------------------------------------------------+\n");

    while (1)
    {
        printf("\n\n+------------------------------------------------------------------------------------------+\n");
        printf("| 1. Probar funciones del punto 2\n");
        printf("| 2. Probar funciones del punto 3\n");
        printf("| 3. Probar funciones del punto 4\n");
        printf("| 4. Probar funciones del punto 6\n");
        printf("| 5. Salir\n");
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
            break;
        case 4:
            break;
        case 5:
            return 0;
        default:
            printf("\nOpcion no valida");
            break;
        }
    }

    return 0;
}

// compile command: gcc -o output ./main.c ./listas_arreglos.c ./tipo_elemento.c ./p2.c && ./output.exe