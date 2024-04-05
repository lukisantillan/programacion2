#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reunionMafia(int nivel)
{
  char *resultado = (char *)malloc((nivel * 4 + 1) * sizeof(char));

  // caso base: cuando se llega al nivel 1
  if (nivel == 1)
  {
    strcpy(resultado, "(-.-)");
    return resultado;
  }

  // se copian los chinos de la izquierda al resultado
  strcpy(resultado, "(-.");

  // se llama recursivamente a la funcion para el nivel anterior y se concatena al resultado
  char *aux = reunionMafia(nivel - 1);
  strcat(resultado, aux);

  // se copian los chinos de la derecha al resultado
  strcat(resultado, ".-)");

  return resultado;
}