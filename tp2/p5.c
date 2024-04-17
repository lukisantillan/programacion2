#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "elementos/tipo_elemento.h"
#include "listas/listas.h"

double calcular_valor_x(Lista list, double x)
{
    double valor_de_x = 0;
    int i;
    TipoElemento item;
    int *aux;
    for (i = 1; i <= l_longitud(list); i++)
    {
        item = l_recuperar(list, i);
        aux = item->valor;
        valor_de_x += pow(x, item->clave) * aux[i - 1];
    }

    return valor_de_x;
}

void hacerPolinomio(Lista list)
{
    int grado, i, grado_multi;
    int coeficiente;
    int *coeficientes;
    int *aux;
    TipoElemento item;
    int inicio_inter, fin_inter, aumentador;

    i = 0;

    printf("\nPor favor, ingrese el grado de su polinomio (0 para terminar): ");
    scanf("%i", &grado);

    printf("\nPor favor, ingrese el coeficiente principal de su polinomio: (0 para terminar): ");
    scanf("%i", &coeficiente);

    coeficientes = malloc(sizeof(int) * (grado + 1));
    item = te_crear_con_valor(grado, coeficientes);

    l_agregar(list, item);
    coeficientes[i] = coeficiente;

    while (grado > 0)
    {
        i++;
        printf("\nPor favor, ingrese el grado de su polinomio (0 para terminar): ");
        scanf("%i", &grado);

        printf("\nPor favor, ingrese el coeficiente principal de su polinomio: (0 para terminar): ");
        scanf("%i", &coeficiente);

        item = te_crear_con_valor(grado, coeficientes);

        coeficientes[i] = coeficiente;
        l_agregar(list, item);
    }

    printf("\n");
    for (i = 1; i <= l_longitud(list); i++)
    {
        item = l_recuperar(list, i);

        aux = item->valor;

        printf("%ix^%i", aux[i - 1], item->clave);
        if (i != l_longitud(list))
        {
            printf("+");
        }
    }
}

Lista calcularRango(Lista list, double x, double y, double sumando)
{
    Lista respuesta;
    TipoElemento item;
    respuesta = l_crear();
    double *valores;
    double cantidad = (fabs(y - x) / sumando) + 1;
    int i = 0;
    valores = malloc(sizeof(double) * cantidad);

    while (x <= y)
    {
        valores[i] = calcular_valor_x(list, x);
        item = te_crear_con_valor(i, valores);
        l_agregar(respuesta, item);
        x += sumando;
        i++;
    }

    return respuesta;
}

/*int main()
{
    int i;
    Lista listilla;
    Lista respuesta;
    TipoElemento item;
    l_crear(respuesta);
    double resp;
    double* array_valores;
    listilla =l_crear();

   polinomio(listilla);

   respuesta=rango(listilla,-1,1,0.5);
   printf("\n");

   l_mostrar(respuesta);

  item= l_recuperar(respuesta,1);

  array_valores=item->valor;

  for ( i = 0; i < l_longitud(respuesta); i++)
  {
    printf("\n %.2f",array_valores[i]);
  }










    return 0;
}*/