#include "listas.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// P2
typedef struct
{
    float resultado1;
    float resultado2;
} Resultados;

typedef struct resultadoStruct
{
    int pos;
    int lista;
    int valor;
} ResultadoValorMaximo;

Lista verElementosRepetidos(Lista l1, Lista l2);

Lista verElementosQueNoSeRepiten(Lista l1, Lista l2);

float promedio(Lista l1);

Resultados promedioAmbasListas(Lista l1, Lista l2);

ResultadoValorMaximo valorMaximo(Lista l1, Lista l2);
// P3

typedef struct
{
    bool esMultiplo;
    bool escalar;
    int numEscalar;
} ResultadosMul;
ResultadosMul multiplo(Lista l1, Lista l2);

// P4
void CompararListas(Lista l1, Lista L2);

// P6

bool esSublista(Lista l1, Lista l2);