#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool divisiblePor7(int n)
{
  if(n < 70)
  {
    return (n == 0) || (n % 7 == 0);
  }

  int ultimoDigito = n % 10;
  int nSinUltimoDigito = n / 10;

  return divisiblePor7(nSinUltimoDigito - 2 * ultimoDigito);
}