#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool palindromo(char *cadena)
{
  int len = strlen(cadena);

  //caso base, si la longitud es 0 o 1, es palindromo
  if (len <= 1)
  {
    return true;
  }

  //si el primer y ultimo caracter son iguales, se llama a la funcion con el string sin esos caracteres
  if (cadena[0] == cadena[len - 1])
  {
    //creo un nuevo string que va a contener el tamaño original - 2 caracteres
    char newStr[len - 2];
    
    //copio el string original en el nuevo string sin el primer caracter
    // for (int i = 1; i < len - 1; i++)
    // {
    //   newStr[i - 1] = str[i];
    // }
    strncpy(newStr, cadena + 1, len - 2);

    //borro el ultimo caracter
    newStr[len - 2] = '\0';
    
    return palindromo(newStr);
  }

  //si el primer y ultimo caracter no son iguales, no es palindromo
  return false;
}