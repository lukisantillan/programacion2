#include <stdio.h>
#include <stdlib.h>

int terminoSeridFibonacci(int k)
{
  // caso base: si k es 0, el termino es 0
  if (k == 0)
  {
    return 0;
  }

  // caso base: si k es 1, el termino es 1
  else if (k == 1)
  {
    return 1;
  }

  // caso recursivo: el termino k es la suma de los dos terminos anteriores
  return terminoSeridFibonacci(k - 1) + terminoSeridFibonacci(k - 2);
}