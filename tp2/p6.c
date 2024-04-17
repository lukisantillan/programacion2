#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./TP_2_Listas.h"

/*
    Ejercicio 6.
    *   Generar un algoritmo que determine si una lista es sublista de otra.  Se considera que es
        una sublista si todos los valores de la segunda se  encuentran dentro de la primera sin
        importar el orden o posición de cada elemento. La comparación es solo por la clave. Se
        pide además determinar la complejidad algorítmica de la solución.
        Ejemplo: si “L1” contiene los elementos (7, 3, 4, 5, 9, 2) y “L2” contiene los elementos
        (4, 7, 2) se dice que “L2” es sublista de “L1”.

    Compilación:
    *   gcc -o p6.output ./p6.c ./listas_punteros.c ./tipo_elemento.c && ./p6.output
        gcc -o p6.output ./p6.c ./listas_cursores.c ./tipo_elemento.c && ./p6.output
        gcc -o p6.output ./p6.c ./listas_arreglos.c ./tipo_elemento.c && ./p6.output
*/

/*
    * Determina si una lista es sublista de otra.
    * @param Lista l1: Lista 1.
    * @param Lista l2: Lista 2.
    * @return bool: Si la lista 2 es sublista de la lista 1.
    * Complejidad algoritmica: O(n)
    * Complejidad algoritmica en listas arreglo: O(n^2)
    * Complejidad algoritmica en listas cursores: O(n^2)
    * Complejidad algoritmica en listas punteros: O(n^2)
*/
bool esSublista(Lista l1, Lista l2)
{
  int len1 = l_longitud(l1);
  int len2 = l_longitud(l2);

  Iterador itl2 = iterador(l2);

  if (len2 > len1 || (len1 == 0 && len2 != 0) || (len2 == 0 && len1 != 0))
  {
    return false;
  }

  bool esSublista = true;

  while (hay_siguiente(itl2))
  {
    TipoElemento actualL2 = siguiente(itl2);
    TipoElemento elementoL1 = l_buscar(l1, actualL2->clave);
    if (elementoL1 == NULL)
    {
      esSublista = false;
      break;
    }
  }

  return esSublista;
}

// int main()
// {
//   Lista l1 = l_crear();
//   Lista l2 = l_crear();
//   l_agregar(l1, te_crear(10));
//   l_agregar(l1, te_crear(1));
//   l_agregar(l1, te_crear(3));
//   l_agregar(l1, te_crear(2));
//   l_agregar(l1, te_crear(4));
//   l_agregar(l2, te_crear(2));
//   l_agregar(l2, te_crear(3));
//   l_agregar(l2, te_crear(4));
//   l_agregar(l2, te_crear(4));
//   l_agregar(l2, te_crear(1));

//   if (esSublista(l1, l2))
//   {
//     printf("La lista 2 es sublista de la lista 1\n");
//   }
//   else
//   {
//     printf("La lista 2 no es sublista de la lista 1\n");
//   }

//   return 0;
// }