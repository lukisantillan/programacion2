#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listas.h"

bool esSublista(Lista l1, Lista l2)
{
  int len1 = l_longitud(l1);
  int len2 = l_longitud(l2);

  Iterador itl1 = iterador(l1);
  Iterador itl2 = iterador(l2);

  if (len2 > len1 || len1 == 0 || len2 == 0)
  {
    return false;
  }

  Lista aux = l_crear();

  while (hay_siguiente(itl2))
  {
    l_agregar(aux, siguiente(itl2));
  }

  Iterador itaux = iterador(aux);

  l_mostrar(l1);
  l_mostrar(aux);

  while (hay_siguiente(itl1))
  {
    TipoElemento actualL1 = siguiente(itl1);
    while (hay_siguiente(itaux))
    {
      TipoElemento actualAux = siguiente(itaux);
      printf("Elemento l1: %d | Elemento aux: %d\n", actualL1->clave, actualAux->clave);
      if (actualAux->clave == actualL1->clave)
      {
        printf("Borrando %d\n", actualAux->clave);
        l_borrar(aux, actualAux->clave);
        reiniciarIterador(itaux, aux);
        break;
      }
    }
  }

  l_mostrar(aux);

  return l_es_vacia(aux);
}

// int main()
// {
//   Lista l1 = l_crear();
//   Lista l2 = l_crear();
//   l_agregar(l1, te_crear(1));
//   l_agregar(l1, te_crear(2));
//   l_agregar(l1, te_crear(3));
//   l_agregar(l1, te_crear(4));
//   l_agregar(l2, te_crear(2));
//   l_agregar(l2, te_crear(1));
//   l_agregar(l2, te_crear(4));
//   l_agregar(l2, te_crear(3));

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