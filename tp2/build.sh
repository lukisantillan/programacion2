#!/bin/bash

echo "Compilando y ejecutando el programa..."
gcc -o compiled.out main.c elementos/tipo_elemento.c listas/listas_arreglos.c p2.c p3.c p4.c p5.c p6.c
./compiled.out

echo "Limpiando archivos..."
rm compiled.out