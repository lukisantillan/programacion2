#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "TP1_Recursividad.h"

void continuar(int *flag)
{
    char *check = (char *)malloc(100 * sizeof(char));
    printf("\n¿DESEA CONTINUAR CON EL MISMO EJERCICIO? (SI - NO):  ");
    scanf("%99s", check);
    // Convertir la cadena a mayúsculas
    for (int i = 0; check[i] != '\0'; i++)
    {
        check[i] = toupper(check[i]);
    }
    if (strcmp(check, "SI") == 0)
    {
        *flag = 0;
    }
    else
    {
        *flag = 1;
    }
    free(check);
}

void test1(){
        int flag = 0;
        char *palabra = (char *)malloc(100*sizeof(char));
        while (flag == 0)
        {
            printf("\nIngrese la palabra a testear:   ");
            fflush(stdin);
            fgets(palabra, sizeof(palabra), stdin);
            // Eliminar el salto de línea del final de la cadena
            palabra[strcspn(palabra, "\n")] = '\0';
            bool resultado = palindromo(palabra);
            if (resultado)
            {
                printf("\nEs un palindromo");
            }
            else
            {
                printf("\nNo es un palindromo");
            }
            continuar(&flag);
            fgets(palabra, sizeof(palabra), stdin);
        }
        free(palabra);
}

void test2() {
    int flag = 0, n1, n2;
    printf("\nTesteo Función punto 2: Producto");
        while (flag == 0)
        {
            printf("\nIngrese el N1 \n");
            scanf("%i", &n1);
            printf("\nIngrese el N2 \n");
            scanf("%i", &n2);
            int resultado = producto(n1, n2);
            printf("\nEl resultado del producto es %i", resultado);
            continuar(&flag);
        }
}

void test3(){
        int flag = 0, n1;
        printf("\nTesteo Función punto 3: Fibonacci");
        while (flag == 0)
        {
            printf("\nIngrese el k-esimo numero a verificar\n");
            scanf("%i", &n1);
            int resultado = terminoSeridFibonacci(n1);
            printf("El %i numero es : %i\n", n1, resultado);
            continuar(&flag);
        }
}

void test4(){
        int flag = 0, n1, n2;
        printf("\nTesteo Función punto 4: Division");
        while (flag == 0)
        {
            printf("\nIngrese el N1 \n");
            scanf("%i", &n1);
            printf("\nIngrese el N2 \n");
            scanf("%i", &n2);
            float resultado = division(n1, n2);
            printf("\nEl resultado de la division es %.5f", resultado);
            continuar(&flag);
        }
}

void test5(){
        int flag = 0;
        while (flag == 0)
        {
            char *numero = (char *)malloc(100*sizeof(char));
            printf("\nIngrese el numero a testear:   ");
            fflush(stdin);
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = '\0';
            char *resultado = agregarSeparadorMiles(numero);
            printf("%s", resultado);
            continuar(&flag);
        }
}

void test6(){
        int flag = 0;
        int numeroDeChinos;
        while (flag == 0)
        {
            printf("\nIngrese la Cantidad de chinos: ");
            scanf("%i", &numeroDeChinos);
            char *resultado = reunionMafia(numeroDeChinos);
            printf("%s", resultado);
            continuar(&flag);
        }
}

void test7(){
        int flag = 0;
        char *secuencia = (char *)malloc(100*sizeof(char));
        while (flag == 0)
        {
            printf("\nIngrese la secuencia de la señal ( H  o L):   ");
            fflush(stdin);
            fgets(secuencia, sizeof(secuencia), stdin);
            char *resultado = ondaDigital(secuencia);
            printf("%s", resultado);
            continuar(&flag);
        }
        free(secuencia);
}


void test9(){
        int flag = 0;
        int numero;
        while (flag == 0)
        {
            printf("\nIngrese el numero a verificar si es divisible por 7: ");
            scanf("%i", &numero);
            bool resultado = divisiblePor7(numero);
            if (resultado)
            {
                printf("\nEl numero es divisible por 7");
            } else {printf("\n El numero no es divisible por 7");}
            continuar(&flag);
        }
}

void testear(int punto){
    switch (punto)
    {
    case 1:
        printf("Testeo Función punto 1: Palindromo\n");
        test1();
        break;
    case 2:
        test2();
        break;
    case 3:
        test3();
        break;
    case 4:
        test4();
        break;
    case 5:
        printf("\nTesteo Función punto 5: Separadormiles");
        test5();
        break;
    case 6: 
        printf("\nTesteo Función punto 6: ReunionMafia");
        test6();
        break;
    case 7:
        printf("\nTesteo Función punto 7: OndaDigital");
        test7();
    case 8:
        break;
    case 9:
        printf("\nTesteo Función punto 9: DivisiblePor7");
        test9();
        break;
    case 10:
        break;
    default:
        break;
    }
}
//FALTA TEST 8 Y 10, Y HACER QUE EL PROFESOR PUEDA SALIR DE LA FUNCION TESTEAR CUANDO QUIERA.
int main()
{
    int punto;
    printf("\n Ingrese el punto a testear");
    scanf("%i", &punto);
    testear(punto);
    return 0;
}
