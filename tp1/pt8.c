#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirSubconjunto(int subconjunto[], int n, char **output) {
  char buffer[100];
  if (**output) {
    strcat(*output, ", ");
  }
  strcat(*output, "{");
  for (int i = 0; i < n; i++) {
    sprintf(buffer, "%d", subconjunto[i]);
    strcat(*output, buffer);
    if (i < n - 1) {
      strcat(*output, ", ");
    }
  }
  strcat(*output, "}");
}

void sumaSubconjunto(int conjunto[], int subconjunto[], int n, int tamSubconjunto, int total, int nodo, int suma, char **output) {
  if (total == suma) {
    imprimirSubconjunto(subconjunto, tamSubconjunto, output); 
    return;
  }
  else {
    for (int i = nodo; i < n; i++) { 
      subconjunto[tamSubconjunto] = conjunto[i];
      sumaSubconjunto(conjunto, subconjunto, n, tamSubconjunto + 1, total + conjunto[i], i + 1, suma, output);
    }
  }
}

void subconjuntosQueSumanN(int conjunto[], int tamano, int n, char **output) {
  int subconjunto[tamano];
  sumaSubconjunto(conjunto, subconjunto, tamano, 0, 0, 0, n, output);
}