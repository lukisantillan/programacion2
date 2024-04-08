#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "TP1_Recursividad.h"

void testPt1()
{
  assert(palindromo("") == true);
  assert(palindromo("a") == true);
  assert(palindromo("neuquen") == true);
  assert(palindromo("palindromo") == false);
  assert(palindromo("n euqu en") == false);
  printf("Punto 1 OK\n");
}

void testPt2()
{
  assert(producto(3, 2) == 6);
  assert(producto(5, 3) == 15);
  assert(producto(10, 4) == 40);
  assert(producto(2, -1) == -2);
  assert(producto(2, -4) == -8);
  assert(producto(-2, 4) == -8);
  assert(producto(-2, -4) == 8);
  assert(producto(2, 0) == 0);
  printf("Punto 2 OK\n");
}

void testPt3()
{
  // este punto se hizo considerando al primer termino de la serie como indice 0 (0, 1, 1, 2, 3, 5, 8, 13, 21, ...)
  assert(terminoSeridFibonacci(0) == 1);
  assert(terminoSeridFibonacci(1) == 1);
  assert(terminoSeridFibonacci(2) == 2);
  assert(terminoSeridFibonacci(5) == 8);
  assert(terminoSeridFibonacci(16) == 1597);
  assert(terminoSeridFibonacci(19) == 6765);
  printf("Punto 3 OK\n");
}

void testPt4()
{
  char str[20];

  sprintf(str, "%.5f", division(22, 3));
  assert(strcmp(str, "7.33333") == 0);

  sprintf(str, "%.5f", division(10, 2));
  assert(strcmp(str, "5.00000") == 0);

  sprintf(str, "%.5f", division(9, 3));
  assert(strcmp(str, "3.00000") == 0);

  sprintf(str, "%.5f", division(-9, -3));
  assert(strcmp(str, "3.00000") == 0);

  sprintf(str, "%.5f", division(9, -3));
  assert(strcmp(str, "-3.00000") == 0);

  printf("Punto 4 OK\n");
}

void testPt5()
{
  assert(strcmp(agregarSeparadorMiles("100"), "100") == 0);
  assert(strcmp(agregarSeparadorMiles("1000"), "1.000") == 0);
  assert(strcmp(agregarSeparadorMiles("100000"), "100.000") == 0);
  assert(strcmp(agregarSeparadorMiles("1000000"), "1.000.000") == 0);
  assert(strcmp(agregarSeparadorMiles("-100"), "-100") == 0);
  assert(strcmp(agregarSeparadorMiles("-1000"), "-1.000") == 0);
  assert(strcmp(agregarSeparadorMiles("-100000"), "-100.000") == 0);
  assert(strcmp(agregarSeparadorMiles("-1000000"), "-1.000.000") == 0);
  printf("Punto 5 OK\n");
}

void testPt6()
{
  assert(strcmp(reunionMafia(1), "(-.-)") == 0);
  assert(strcmp(reunionMafia(2), "(-.(-.-).-)") == 0);
  assert(strcmp(reunionMafia(3), "(-.(-.(-.-).-).-)") == 0);
  assert(strcmp(reunionMafia(4), "(-.(-.(-.(-.-).-).-).-)") == 0);
  printf("Punto 6 OK\n");
}

void testPt7()
{
  assert(strcmp("_|--|_", ondaDigital("LHHL")) == 0);
  assert(strcmp("-|__|-", ondaDigital("HLLH")) == 0);
  assert(strcmp("-|_|-|_", ondaDigital("HLHL")) == 0);
  printf("Punto 7 OK\n");
}

void testPt8()
{
  int conjunto[] = {10,3,7,1,4,2};
  int objetivo = 7;
  int tamano = sizeof(conjunto) / sizeof(conjunto[0]);

  char* output = malloc(100 * sizeof(char));
  output[0] = '\0';

  subconjuntosQueSumanN(conjunto, tamano, objetivo, &output);

  assert(strcmp(output, "{3, 4}, {7}, {1, 4, 2}") == 0);
  free(output);

  printf("Punto 8 OK\n");
}

void testPt9()
{
  assert(divisiblePor7(0) == true);
  assert(divisiblePor7(7) == true);
  assert(divisiblePor7(110) == false);
  assert(divisiblePor7(32291) == true);
  assert(divisiblePor7(-32291) == true);
  printf("Punto 9 OK\n");
}

void testPt10()
{
  // se definen los parametros y el resultado esperado
  int n = 10;
  int b = 3;
  int* esperado = (int[]){3, 2, 1, 1, 3};

  // logica del test
  int max = n / b + 1;
  int* resultado = malloc((max + 1) * sizeof(int));
  resultado = explosion(n, b);
  for (int i = 0; i <= max ; i++)
  {
    assert(resultado[i] == esperado[i]);
  }
  free(resultado);

  printf("Punto 10 OK\n");
}

/*
int main()
{
  testPt1();
  testPt2();
  testPt3();
  testPt4();
  testPt5();
  testPt6();
  testPt7();
  testPt8();
  testPt9();
  testPt10();
  return 0;
}
*/