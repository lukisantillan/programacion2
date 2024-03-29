#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"

void testPt1()
{
  assert(palindromo("") == true);
  assert(palindromo("a") == true);
  assert(palindromo("neuquen") == true);
  assert(palindromo("palindromo") == false);
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
  // sucesion de fibonacci (empezando desde el termino 0): 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
  assert(terminoFibo(0) == 0);
  assert(terminoFibo(1) == 1);
  assert(terminoFibo(2) == 1);
  assert(terminoFibo(5) == 5);
  assert(terminoFibo(17) == 1597);
  assert(terminoFibo(20) == 6765);
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
  assert(strcmp(agregarSeparadorMiles("1000000"), "1.000.000") == 0);
  printf("Punto 5 OK\n");
}

void testPt6()
{
  assert(strcmp(formacionChina(1), "(-.-)") == 0);
  assert(strcmp(formacionChina(2), "(-.(-.-).-)") == 0);
  assert(strcmp(formacionChina(3), "(-.(-.(-.-).-).-)") == 0);
  assert(strcmp(formacionChina(4), "(-.(-.(-.(-.-).-).-).-)") == 0);
  printf("Punto 6 OK\n");
}

void testPt7()
{
  // si hay mas de un test, falla porque usa una variable estatica para el resultado
  assert(strcmp("_|--|_", ondaDigital("LHHL")) == 0);
  assert(strcmp("-|__|-", ondaDigital("HLLH")) == 0);
  assert(strcmp("-|_|-|_", ondaDigital("HLHL")) == 0);
  printf("Punto 7 OK\n");
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
  // hacer
}

int main()
{
  testPt1();
  testPt2();
  testPt3();
  testPt4();
  testPt5();
  testPt6();
  testPt7();
  testPt9();
  return 0;
}