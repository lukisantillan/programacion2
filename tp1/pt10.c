#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bombita(int A, int B, int *vec, int *indice)
{
  int resultado;
  if (A <= B)
  {
    vec[(*indice)++] = B;

    return;
  }

  int n1 = A / B;
  int n2 = A - (A / B);

  if (n1 > B)
  {
    resultado = n1;
  }
  else
  {
    vec[(*indice)++] = n1;
  }
  if (n2 >= B)
  {
    resultado = n2;
  }
  else
  {
    vec[(*indice)++] = n2;
  }
  return bombita(resultado, B, vec, indice);
}

int* explosion(int n, int b)
{
  int *vec;
  int puntero = 0; // indice del vector
  int max;

  // calculo la cantidad maxima de elementos
  max = n / b + 1;
  // asigno memoria dinamica a un puntero(vector)
  vec = malloc(sizeof(int) * max);
  bombita(n, b, vec, &puntero);

  return vec;
}