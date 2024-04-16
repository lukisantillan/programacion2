#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ejercicios.h"
#include "listas.h"

void testPt2()
{
    Lista lista1 = l_crear();
    Lista lista2 = l_crear();

    char elemento[100];

    while (1)
    {
        printf("\n1. Rellenar lista 1: input de elementos hasta que se ingrese 'fin'");
        printf("\n2. Rellenar lista 2: input de elementos hasta que se ingrese 'fin'");
        printf("\n3. Ver elementos repetidos");
        printf("\n4. Ver elementos que no se repiten");
        printf("\n5. Ver promedio de la lista 1");
        printf("\n6. Ver promedio de la lista 2");
        printf("\n7. Ver resultado maximo de ambas listas");
        printf("\n8. Salir");
        printf("\nIngrese una opcion: ");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            while (1)
            {
                printf("\nIngrese elementos de la lista 1: ");
                scanf("%s", elemento);
                if (strcmp(elemento, "fin") == 0)
                {
                    break;
                }
                l_agregar(lista1, (TipoElemento)strdup(elemento));
            }
            break;
        case 2:
            while (1)
            {
                printf("\nIngrese elementos de la lista 2: ");
                scanf("%s", elemento);
                if (strcmp(elemento, "fin") == 0)
                {
                    break;
                }
                l_agregar(lista2, (TipoElemento)strdup(elemento));
            }
            break;
        case 3:
            //verElementosRepetidos(lista1, lista2);
            //printf("\nElementos repetidos: ");
            //l_mostrar(listaRepetidos);
            break;
        case 4:
            //l_mostrar(verElementosQueNoSeRepiten(lista1, lista2));
            break;
        case 5:
            //promedio1 = promedio(lista1);
            //printf("\nPromedio de la lista 1: %.2f", promedio1);
            break;
        case 6:
            //promedio2 = promedio(lista2);
            //printf("\nPromedio de la lista 2: %.2f", promedio2);
            break;
        case 7:
            //Resultados resu;
            //resu.resultado1 = promedio(lista1);
            //resu.resultado2 = promedio(lista2);
            //return resu;
            break;
        case 8:
            return;
        default:
            printf("\nOpcion invalida");
            break;
        }
    }
}

int main()
{
    // Falta agregar menu principal
    testPt2();

    return 0;
}

// compile command: gcc -o output ./tp2/tipo_elemento.c ./tp2/listas_arreglos.c ./tp2/main.c