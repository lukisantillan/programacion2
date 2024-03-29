#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *formacionChina(int grado)
{
  char *resultado = (char *)malloc((grado * 4 + 1) * sizeof(char));

  // caso base: cuando se llega al grado 1
  if (grado == 1)
  {
    strcpy(resultado, "(-.-)");
    return resultado;
  }

  // se copian los chinos de la izquierda al resultado
  strcpy(resultado, "(-.");

  // se llama recursivamente a la funcion para el grado anterior y se concatena al resultado
  char *aux = formacionChina(grado - 1);
  strcat(resultado, aux);
  free(aux);

  // se copian los chinos de la derecha al resultado
  strcat(resultado, ".-)");

  return resultado;
}