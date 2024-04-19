##!/bin/bash

echo "Verificando si existe el directorio compiled..."
if [ ! -d "compiled" ]; then
    mkdir compiled
fi

echo "Compilando y ejecutando el programa..."
gcc -o compiled/arreglos.out ejercicios.c ../libs/elementos/tipo_elemento.c ../libs/pilas/pilas_arreglos.c
gcc -o compiled/punteros.out ejercicios.c ../libs/elementos/tipo_elemento.c ../libs/pilas/pilas_punteros.c

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