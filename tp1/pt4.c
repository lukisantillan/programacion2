#include <stdio.h>
#include <stdlib.h>

float division(int n, int m)
{
  // caso base: si n es menor a m, deja de llamar a la funcion y retorna la parte decimal del resultado
  if (abs(n) < abs(m))
  {
    return (float)n / m; // hay que castear a float porque la division de dos enteros da un entero
  }

  float result;

  // si n y m son ambos positivos o negativos, el resultado es positivo
  if (n < 0 && m < 0 || n > 0 && m > 0)
  {
    result = 1 + division(abs(n) - abs(m), abs(m));
  }

  // si uno de los dos es positivo y el otro negativo, el resultado es negativo
  if (n < 0 && m > 0|| m < 0 && n > 0)
  {
    result = (1 + division(abs(n) - abs(m), abs(m))) * -1;
  }

  return result;
}