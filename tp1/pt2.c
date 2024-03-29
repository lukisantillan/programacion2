#include <stdio.h>
#include <stdlib.h>

int producto(int m, int n)
{

  // checkeo si alguno de los dos numeros es 0
  if (n == 0)
  {
    // si n es 0, el producto es 0
    return 0;
  }

  // si n es negativo, llamo a la funcion con n positivo y cambio el signo del resultado
  if (n < 0)
  {
    return -producto(m, -n);
  }

  // si n es positivo, sumo m n veces
  return m + producto(m, n - 1);
}