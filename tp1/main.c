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
	printf("\nDesea continuar? (Si/No): ");
	scanf("%99s", check);
	// Convertir la cadena a mayusculas
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

void test1()
{
	int flag = 0;
	char *palabra = (char *)malloc(100 * sizeof(char));
	while (flag == 0)
	{
		printf("\nIngrese la palabra a testear: ");
		fflush(stdin);
		fgets(palabra, sizeof(palabra), stdin);
		// Eliminar el salto de linea del final de la cadena
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

void test2()
{
	int flag = 0, n1, n2;
	while (flag == 0)
	{
		printf("\nIngrese el N1: ");
		scanf("%i", &n1);
		printf("\nIngrese el N2: ");
		scanf("%i", &n2);
		int resultado = producto(n1, n2);
		printf("\nEl resultado del producto es %i", resultado);
		continuar(&flag);
	}
}

void test3()
{
	int flag = 0, n1;
	while (flag == 0)
	{
		printf("\nIngrese el k-esimo numero a verificar\n");
		scanf("%i", &n1);
		int resultado = terminoSeridFibonacci(n1);
		printf("El %i numero es : %i\n", n1, resultado);
		continuar(&flag);
	}
}

void test4()
{
	int flag = 0, n1, n2;
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

void test5()
{
	int flag = 0;
	while (flag == 0)
	{
		char *numero = (char *)malloc(100 * sizeof(char));
		printf("\nIngrese el numero a testear:   ");
		fflush(stdin);
		fgets(numero, sizeof(numero), stdin);
		numero[strcspn(numero, "\n")] = '\0';
		char *resultado = agregarSeparadorMiles(numero);
		printf("%s", resultado);
		continuar(&flag);
	}
}

void test6()
{
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

void test7()
{
	int flag = 0;
	char *secuencia = (char *)malloc(100 * sizeof(char));
	while (flag == 0)
	{
		printf("\nIngrese la secuencia de la senal (H o L): ");
		fflush(stdin);
		fgets(secuencia, sizeof(secuencia), stdin);
		char *resultado = ondaDigital(secuencia);
		printf("%s", resultado);
		continuar(&flag);
	}
	free(secuencia);
}

void test8()
{
	int flag = 0;

	printf("\nIngrese el tamano del conjunto: ");
	int tamano;
	scanf("%i", &tamano);

	int *conjunto = (int *)malloc(tamano * sizeof(int));
	int objetivo;
	int encontrado = 0;

	char *output = malloc(100 * sizeof(char));
	output[0] = '\0';

	while (flag == 0)
	{
		printf("\nIngrese los %i numeros para el conjunto:\n", tamano);
		for (int i = 0; i < tamano; i++)
		{
			printf("Numero %d: ", i + 1);
			scanf("%d", &conjunto[i]);
		}

		printf("Ingrese el numero objetivo: ");
		scanf("%d", &objetivo);

		subconjuntosQueSumanN(conjunto, tamano, objetivo, &output);
		// print output
		printf("%s", output);
		free(output);

		continuar(&flag);
	}
}

void test9()
{
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
		}
		else
		{
			printf("\n El numero no es divisible por 7");
		}
		continuar(&flag);
	}
}

void test10()
{

	int flag = 0;
	int numero;
	while (flag == 0)
	{
		int n;
		int b;
		printf("\n Ingrese el numero: ");
		scanf("%i", &n);
		printf("\n Ingrese la boma: ");
		scanf("%i", &b);

		int max = n / b + 1;
		int *resultado = malloc((max + 1) * sizeof(int));
		resultado = explosion(n, b);
		for (int i = 0; i <= max; i++)
		{
			printf("%i", resultado[i]);
		}
		free(resultado);
		continuar(&flag);
	}
}

void testear(int punto)
{
	switch (punto)
	{
	case 1:
		printf("\nTesteo Funcion punto 1: Palindromo");
		test1();
		break;
	case 2:
		printf("\nTesteo Funcion punto 2: Producto");
		test2();
		break;
	case 3:
		printf("\nTesteo Funcion punto 3: Fibonacci");
		test3();
		break;
	case 4:
		printf("\nTesteo Funcion punto 4: Division");
		test4();
		break;
	case 5:
		printf("\nTesteo Funcion punto 5: Separadormiles");
		test5();
		break;
	case 6:
		printf("\nTesteo Funcion punto 6: ReunionMafia");
		test6();
		break;
	case 7:
		printf("\nTesteo Funcion punto 7: OndaDigital");
		test7();
	case 8:
		printf("\nTesteo Funcion punto 8: SubconjuntosQueSumanN");
		test8();
		break;
	case 9:
		printf("\nTesteo Funcion punto 9: DivisiblePor7");
		test9();
		break;
	case 10:
		printf("\nTesteo Funcion punto 10: Explosion");
		test10();
		break;
	default:
		break;
	}
}

int main()
{
	while (1)
	{
		int punto;
		printf("\n");
		printf("\n1. Palindromo");
		printf("\n2. Producto");
		printf("\n3. Fibonacci");
		printf("\n4. Division");
		printf("\n5. SeparadorMiles");
		printf("\n6. ReunionMafia");
		printf("\n7. OndaDigital");
		printf("\n8. SubconjuntosQueSumanN");
		printf("\n9. DivisiblePor7");
		printf("\n10. Explosion");
		printf("\n");
		printf("\n 0. Salir");
		printf("\n");
		printf("\nIngrese el punto a testear: ");

		scanf("%i", &punto);
		if (punto == 0)
		{
			break;
		}
		testear(punto);
	}

	return 0;
}
