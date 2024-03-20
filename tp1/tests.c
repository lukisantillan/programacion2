#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "funciones.h"

void testPt1()
{
  assert(palindromo("") == true);
  assert(palindromo("a") == true);
  assert(palindromo("neuquen") == true);
  assert(palindromo("palindromo") == false);
  printf("Punto 1 OK\n");
}

int main()
{
  testPt1();
  return 0;
}