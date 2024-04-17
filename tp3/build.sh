##!/bin/bash

echo "Compilando y ejecutando el programa..."
gcc -o compiled/arreglos.out main.c ../libs/elementos/tipo_elemento.c ../libs/pilas/pilas_arreglos.c
gcc -o compiled/punteros.out main.c ../libs/elementos/tipo_elemento.c ../libs/pilas/pilas_punteros.c

clear
echo "Que tipo de pila desea utilzar?"
echo "1. Arreglos"
echo "2. Punteros"
echo "3. Salir"

read -p "Ingrese el número de la opción deseada: " option

clear
case $option in
    1)
        ./compiled/arreglos.out
        ;;
    2)
        ./compiled/punteros.out
        ;;
    3)
        echo "Saliendo..."
        ;;
    *)
        echo "Opción inválida"
        ;;
esac