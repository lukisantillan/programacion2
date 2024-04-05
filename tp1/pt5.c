#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *agregarSeparadorMiles(char num[])
{
  // caso base: si la longitud del número es menor o igual a 3, no se agregan puntos
  int len = strlen(num);
  if (num == NULL || len <= 3)
  {
    return num;
  }

  // si el numero es negativo, se agrega un "-" al principio y se llama recursivamente con el resto del número
  if (num[0] == '-')
  {
    char *resto = malloc((len - 1) * sizeof(char));
    strcpy(resto, num + 1);
    resto[len - 1] = '\0';

    char *resultado = malloc((len + 1) * sizeof(char));
    strcpy(resultado, "-");
    strcat(resultado, agregarSeparadorMiles(resto));

    return resultado;
  }

  // calcular la cantidad de puntos que se van a agregar
  int puntos = (len - 1) / 3;
  int lenFinal = len + puntos;

  // separar los ultimos tres digitos del resto del número
  char *resto = malloc((len - 3) * sizeof(char));
  strcpy(resto, num);
  resto[len - 3] = '\0';

  char *ultimosTres = malloc(5 * sizeof(char));
  strcpy(ultimosTres, num + len - 3);

  // agregar un punto al principio de los ultimos tres digitos
  char *ultimosTresConPunto = malloc(5 * sizeof(char));
  strcpy(ultimosTresConPunto, ".");
  strcat(ultimosTresConPunto, ultimosTres);

  // llamar recursivamente a la función con el resto del número (para que separe los ultimos 3 digitos y agregue el punto hasta que queden menos de 3 digitos)
  char *resultado = malloc(lenFinal * sizeof(char));
  strcpy(resultado, agregarSeparadorMiles(resto));
  strcat(resultado, ultimosTresConPunto);

  return resultado;
}