#include <stdio.h>
#include <stdlib.h>

float division(float n1, float n2)
{
  if (abs(n1) < abs(n2))
  {
    return n1 / n2;
  }

  float result;

  if (n1 < 0 && n2 < 0 || n1 > 0 && n2 > 0)
  {
    result = 1 + division(abs(n1) - abs(n2), abs(n2));
  }

  if (n1 < 0 && n2 > 0|| n2 < 0 && n1 > 0)
  {
    result = (1 + division(abs(n1) - abs(n2), abs(n2))) * -1;
  }

  return result;
}