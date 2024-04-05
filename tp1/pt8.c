#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// esto solamente busca subconjuntos sin repetir numeros, al final queda un subconjunto incompleto
void encontrarSubconjuntosQueSumenN(char *resultado, int conjunto[], int n, int conjuntoOriginal[], int nOriginal)
{
  if (n == 0)
  {
    strcat(resultado, "| ");
    encontrarSubconjuntosQueSumenN(resultado, conjunto , nOriginal, conjuntoOriginal, nOriginal);
    return;
  }

  if (conjunto[0] == '\0')
  {
    return;
  }

  if (conjunto[0] > n)
  {
    encontrarSubconjuntosQueSumenN(resultado, conjunto + 1, n, conjuntoOriginal, nOriginal);
    return;
  }

  char *primerElemento = malloc(1000);
  sprintf(primerElemento, "%d ", conjunto[0]);
  strcat(resultado, primerElemento);
  encontrarSubconjuntosQueSumenN(resultado, conjunto + 1, n - conjunto[0], conjuntoOriginal, nOriginal);
}

// buscar la forma de que el tamaño no se tenga que pasar como parametro
char *subconjuntosQueSumanN(int conjunto[], int n, int tamano)
{
  char *resultado = malloc(1000);
  resultado[0] = '\0';

  int conjuntoOrdenado[tamano];
  for (int i = 0; i < tamano; i++)
  {
    conjuntoOrdenado[i] = conjunto[i];
  }

  for (int i = 0; i < tamano; i++)
  {
    for (int j = i + 1; j < tamano; j++)
    {
      if (conjuntoOrdenado[i] < conjuntoOrdenado[j])
      {
        int aux = conjuntoOrdenado[i];
        conjuntoOrdenado[i] = conjuntoOrdenado[j];
        conjuntoOrdenado[j] = aux;
      }
    }
  }

  encontrarSubconjuntosQueSumenN(resultado, conjuntoOrdenado, n, conjunto, n);

  return resultado;
}