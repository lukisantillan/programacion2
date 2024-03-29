#include <stdio.h>
#include <stdlib.h>

int terminoFibo(int n)
{
  // caso base: si n es 0, el termino es 0
  if (n == 0)
  {
    return 0;
  }

  // caso base: si n es 1, el termino es 1
  else if (n == 1)
  {
    return 1;
  }

  // caso recursivo: el termino n es la suma de los dos terminos anteriores
  return terminoFibo(n - 1) + terminoFibo(n - 2);
}