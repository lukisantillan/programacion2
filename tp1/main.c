#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h> 
#include <string.h>
#include "TP1_Recursividad.h"

void continuar(int *flag){
        char *check = (char *)malloc(100 * sizeof(char));
        printf("\n¿DESEA CONTINUAR? (SI - NO):  ");
        scanf("%99s", check);
        // Convertir la cadena a mayúsculas
        for (int i = 0; check[i] != '\0'; i++)
        {
            check[i] = toupper(check[i]);
        }
        if (strcmp(check, "SI") == 0)
        {
            *flag = 0;
        } else {*flag = 1;}
}

int main()
{
    int flag = 0;
    //Variables Ejercicio 1
    char *palabra = (char *)malloc(100 * sizeof(char));

    //Variables Ejercicio 2y3
    int n1, n2;

    //EJERCICIO1
    printf("Testeo Función punto 1: Palindromo\n");
    while (flag == 0) { 
        printf("Ingrese la palabra a testear:   ");
        fgets(palabra, sizeof(palabra), stdin);
        // Eliminar el salto de línea del final de la cadena
        palabra[strcspn(palabra, "\n")] = '\0';
        bool resultado = palindromo(palabra);
        if (resultado)
        {
            printf("\nEs un palindromo");
        } else {printf("\nNo es un palindromo");}
        continuar(&flag);
        fgets(palabra, sizeof(palabra), stdin);
    }

    //EJERCICIO2
    flag = 0;
    printf("\nTesteo Función punto 2: Producto");
    printf("\nIngrese el N1 \n");
    scanf("%i", &n1);
    while (flag == 0)
    {
        printf("\nIngrese el N2 \n");
        scanf("%i", &n2);
        int resultado = producto(n1,n2);
        printf("\nEl resultado del producto es %i", resultado);
        continuar(&flag);
    }   
    
    //EJERCICIO3
    flag = 0;
    printf("\nTesteo Función punto 3: Fibonacci");
    while (flag == 0)
    {
        printf("\nIngrese el k-esimo numero a verificar\n");
        scanf("%i", &n1);
        int resultado = terminoSeridFibonacci(n1);
        printf("El %i numero es : %i\n", n1, resultado);
        continuar(&flag);
    }
    

    return 0;
}

