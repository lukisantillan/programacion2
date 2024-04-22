##!/bin/bash

echo "Verificando si existe el directorio compiled..."
if [ ! -d "compiled" ]; then
    mkdir compiled
fi

echo "Compilando y ejecutando el programa..."

gcc -o compiled/arreglos_circular.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos_circular.c ../libs/pilas/pilas_arreglos.c  ../libs/listas/listas_arreglos.c 
gcc -o compiled/arreglos.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos.c ../libs/pilas/pilas_arreglos.c ../libs/listas/listas_arreglos.c
gcc -o compiled/punteros.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_punteros.c ../libs/pilas/pilas_arreglos.c ../libs/listas/listas_arreglos.c

gcc -o compiled/arreglos_circular.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos_circular.c ../libs/pilas/pilas_arreglos.c  ../libs/listas/listas_cursores.c 
gcc -o compiled/arreglos.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos.c ../libs/pilas/pilas_arreglos.c ../libs/listas/listas_cursores.c
gcc -o compiled/punteros.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_punteros.c ../libs/pilas/pilas_arreglos.c ../libs/listas/listas_cursores.c

gcc -o compiled/arreglos_circular.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos_circular.c ../libs/pilas/pilas_arreglos.c  ../libs/listas/listas_punteros.c 
gcc -o compiled/arreglos.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos.c ../libs/pilas/pilas_arreglos.c ../libs/listas/listas_punteros.c
gcc -o compiled/punteros.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_punteros.c ../libs/pilas/pilas_arreglos.c ../libs/listas/listas_punteros.c

gcc -o compiled/arreglos_circular.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos_circular.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_arreglos.c 
gcc -o compiled/arreglos.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_arreglos.c 
gcc -o compiled/punteros.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_punteros.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_arreglos.c 

gcc -o compiled/arreglos_circular.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos_circular.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_punteros.c 
gcc -o compiled/arreglos.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_punteros.c 
gcc -o compiled/punteros.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_punteros.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_punteros.c 

gcc -o compiled/arreglos_circular.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos_circular.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_arreglos.c 
gcc -o compiled/arreglos.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_arreglos.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_arreglos.c 
gcc -o compiled/punteros.out main.c ../libs/elementos/tipo_elemento.c ../libs/colas/colas_punteros.c ../libs/pilas/pilas_punteros.c ../libs/listas/listas_arreglos.c 



echo "Que tipo de colas desea utilzar?"
echo "1. Arreglos circular"
echo "2. Arreglos"
echo "3. Punteros"
echo "4. Salir"

read -p "Ingrese el número de la opción deseada: " option

clear
case $option in
    1)
        ./compiled/arreglos_circular.out
        ;;
    2)
        ./compiled/arreglos.out
        ;;
    3)
        ./compiled/punteros.out
        ;;
    4)
        echo "Saliendo..."
        ;;
    *)
        echo "Opción inválida"
        ;;
esac