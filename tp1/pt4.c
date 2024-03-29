#include <stdio.h>
#include <stdlib.h>

// dsp veo

float division(float n1, float n2)
{
  if (n1 < n2)
  {
    return n1 / n2;
  }

  float result = 1 + division(n1 - n2, n2);

  return result;
}