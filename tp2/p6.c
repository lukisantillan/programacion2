#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listas.h"
#include "ejercicios.h"

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

// gcc -o output ./tp2/p6.c ./tp2/listas_punteros.c ./tp2/tipo_elemento.c && ./output
// gcc -o output ./tp2/p6.c ./tp2/listas_cursores.c ./tp2/tipo_elemento.c && ./output
// gcc -o output ./tp2/p6.c ./tp2/listas_arreglos.c ./tp2/tipo_elemento.c && ./output