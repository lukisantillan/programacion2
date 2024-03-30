#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ondaDigitalHelper(char *str, char *result, char prev)
{
  // caso base: se llega al ultimo caracter del string
  if (*str == '\0')
  {
    return;
  }

  // si el caracter actual es distinto al anterior, se agrega un separador
  if (prev != '\0' && *str != prev)
  {
    strcat(result, "|");
  }

  // se agrega el caracter actual al resultado
  if (*str == 'H' || *str == 'h')
  {
    strcat(result, "-");
  }
  else if (*str == 'L' || *str == 'l')
  {
    strcat(result, "_");
  }

  // se llama recursivamente con el siguiente caracter, un puntero al resultado y el caracter actual como previo
  ondaDigitalHelper(str + 1, result, *str);
}

char *ondaDigital(char seniales[])
{
  // se define el resultado como un string vacio
  char *result = malloc(strlen(seniales) * 2 + 1);
  result[0] = '\0';

  // se llama a la funcion auxiliar con el string original, el puntero al resultado y un caracter nulo como previo
  ondaDigitalHelper(seniales, result, '\0');

  // se retorna el resultado
  return result;
}